#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "bmpReader.h"
#include "comparators.h"

BMPFile* loadBMPFile(char* fileName) {
	FILE* filePointer = fopen(fileName, "rb");
	if (!filePointer) {
		printf("Can't load file %s\nPlease, enter correct path: ", fileName);
		return 1;
	}
	BMPFile* bmpFile = malloc(sizeof(BMPFile));

	fread(&bmpFile->bhdr, sizeof(BITMAPFILEHEADER), 1, filePointer);
	fread(&bmpFile->dhdr, sizeof(BITMAPINFOHEADER), 1, filePointer);
	

	bmpFile->data = (unsigned char*)malloc(bmpFile->dhdr.sizeData);
	fseek(filePointer, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fread(bmpFile->data, bmpFile->dhdr.sizeData, 1, filePointer);
	
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	bmpFile->array = (Pixel*)malloc(width * height * sizeof(Pixel));

	int alphaChannel = (bytesPerPixel == 4);
	int j = 0;
	for (int i = 0; i < height * width * bytesPerPixel; i += bytesPerPixel) {
		bmpFile->array[j].blue = bmpFile->data[i];
		bmpFile->array[j].green = bmpFile->data[i+ 1];
		bmpFile->array[j].red = bmpFile->data[i + 2];
		j++;
	}
	fclose(filePointer);
	return bmpFile;
}

void freeBMPFile(BMPFile* bmpFile) {
	if (bmpFile)
		free(bmpFile);
}

void printBMP(BMPFile* bmpFile) {
	for (int i = 0; i < bmpFile->dhdr.sizeData; i++) {
		if (i % 16 == 0) 
			printf("\n%04x: ", i);
		printf("%02x ", bmpFile->data[i]);
	}
}

void createCopy(BMPFile* bmpFile, FILE** newFile, char* fileName) {
	*newFile = fopen(fileName, "w+b");
	if (newFile == NULL) {
		printf("Error. Can't create file.");
		exit(1);
	}
	fwrite(&bmpFile->bhdr, sizeof(BITMAPFILEHEADER), 1, *newFile);
	fwrite(&bmpFile->dhdr, sizeof(BITMAPINFOHEADER), 1, *newFile);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fwrite(bmpFile->data, bmpFile->dhdr.sizeData, 1, *newFile);

	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	bmpFile->array = (Pixel*)malloc(bmpFile->dhdr.sizeData * sizeof(Pixel));
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int alphaChannel = (bytesPerPixel == 4);
	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		bmpFile->array[i].blue = bmpFile->data[i];
		bmpFile->array[i].green = bmpFile->data[i + 1];
		bmpFile->array[i].red = bmpFile->data[i + 2];
		fwrite(&bmpFile->array[i].blue, sizeof(unsigned char), 1, *newFile);
		fwrite(&bmpFile->array[i].green, sizeof(unsigned char), 1, *newFile);
		fwrite(&bmpFile->array[i].red, sizeof(unsigned char), 1, *newFile);
	}
}

void createNegativeImage(BMPFile* bmpFile, FILE** newFile, char* fileName) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	int alphaChannel = (bytesPerPixel == 4);
	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		unsigned char byte0 = 255 - bmpFile->array[i].blue;
		unsigned char byte1 = 255 - bmpFile->array[i].green;
		unsigned char byte2 = 255 - bmpFile->array[i].red;
		unsigned char byte3 = 255;
		fwrite(&byte0, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte1, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte2, sizeof(unsigned char), 1, *newFile);
		if (alphaChannel) {
			fwrite(&byte3, sizeof(unsigned char), 1, *newFile);
		}
	}
	fclose(*newFile);
}

void createBWImage(BMPFile* bmpFile, FILE** newFile, char* fileName) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	int alphaChannel = (bytesPerPixel == 4);
	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		unsigned char byte = (bmpFile->array[i].blue * 0.11 + bmpFile->array[i].red * 0.3 + bmpFile->array[i].green * 0.59);
		fwrite(&byte, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte, sizeof(unsigned char), 1, *newFile);
		if (alphaChannel) {
			fwrite(&byte, sizeof(unsigned char), 1, *newFile);
		}
	}
	fclose(*newFile);
}

void GammaCorrection(BMPFile* bmpFile, FILE** newFile, float gamma, char* fileName) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	int alphaChannel = (bytesPerPixel == 4);

	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		float blue = (float)bmpFile->array[i].blue / 255.0;
		float green = (float)bmpFile->array[i].green / 255.0;
		float red = (float)bmpFile->array[i].red / 255.0;

		blue = (powf(blue, 1.0 / gamma) * 255.0);
		green = (powf(green, 1.0 / gamma) * 255.0);
		red = (powf(red, 1.0 / gamma) * 255.0);

		unsigned char r, g, b;
		r = red;
		g = green;
		b = blue;

		fwrite(&b, sizeof(unsigned char), 1, *newFile);
		fwrite(&g, sizeof(unsigned char), 1, *newFile);
		fwrite(&r, sizeof(unsigned char), 1, *newFile);
	}
		fclose(*newFile);
}

int compare(const void* a, const void* b) {
	return (*(unsigned char*)a - *(unsigned char*)b);
}

//void medianFilter(BMPFile* bmpFile, FILE** newFile, char* fileName, int filterSize) {
//	createCopy(bmpFile, newFile, fileName);
//	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
//	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
//	int width = bmpFile->dhdr.width;
//	int height = bmpFile->dhdr.height;
//	
//	Pixel** pixels = (Pixel**)malloc(header.dibHeader.height * sizeof(Pixel*));
//	for (int i = 0; i < header.dibHeader.height; i++) {
//		pixels[i] = (Pixel*)malloc(header.dibHeader.width * sizeof(Pixel));
//		fread(pixels[i], sizeof(Pixel), header.dibHeader.width, inputFilePtr);
//	}
//
//	Pixel** newPixels = (Pixel**)malloc(header.dibHeader.height * sizeof(Pixel*));
//	for (int i = 0; i < header.dibHeader.height; i++) {
//		newPixels[i] = (Pixel*)malloc(header.dibHeader.width * sizeof(Pixel));
//		memcpy(newPixels[i], pixels[i], header.dibHeader.width * sizeof(Pixel));
//	}
//
//	int halfFilterSize = filterSize / 2;
//
//	for (int i = halfFilterSize; i < header.dibHeader.height - halfFilterSize; i++) {
//		for (int j = halfFilterSize; j < header.dibHeader.width - halfFilterSize; j++) {
//			unsigned char* redValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			unsigned char* greenValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			unsigned char* blueValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			int index = 0;
//			for (int k = -halfFilterSize; k <= halfFilterSize; k++) {
//				for (int l = -halfFilterSize; l <= halfFilterSize; l++) {
//					int x = j + k;
//					int y = i + l;
//					if (y >= 0 && y < header.dibHeader.height && x >= 0 && x < header.dibHeader.width && index >= 0 && index < filterSize * filterSize) {
//						redValues[index] = pixels[y][x].red;
//						greenValues[index] = pixels[y][x].green;
//						blueValues[index] = pixels[y][x].blue;
//					}
//					index++;
//				}
//			}
//			qsort(redValues, index, sizeof(unsigned char), compare);
//			qsort(greenValues, index, sizeof(unsigned char), compare);
//			qsort(blueValues, index, sizeof(unsigned char), compare);
//			newPixels[i][j].red = redValues[index / 2];
//			newPixels[i][j].green = greenValues[index / 2];
//			newPixels[i][j].blue = blueValues[index / 2];
//			free(redValues);
//			free(greenValues);
//			free(blueValues);
//		}
//	}
//
//	for (int i = 0; i < header.dibHeader.height; i++) {
//		fwrite(newPixels[i], sizeof(Pixel), header.dibHeader.width, outputFilePtr);
//		free(pixels[i]);
//		free(newPixels[i]);
//	}
//
//	free(pixels);
//	free(newPixels);
//
//	fclose(inputFilePtr);
//	fclose(outputFilePtr);
//}

//void medianFilter(BMPFile* bmpFile, FILE** newFile, char* fileName, int filterSize) {
//	createCopy(bmpFile, newFile, fileName);
//	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
//	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
//	int width = bmpFile->dhdr.width;
//	int height = bmpFile->dhdr.height;
//	//Pixel* newPixels = (Pixel*)malloc(width * height * sizeof(Pixel));
//	//for (int i = 0; i < height * width; i++) {
//	//	newPixels[i].blue = bmpFile->array[i].blue;
//	//	newPixels[i].green = bmpFile->array[i].green;
//	//	newPixels[i].red = bmpFile->array[i].red;
//	//}
//	//memcpy(newPixels, bmpFile->array, width * height * sizeof(Pixel));
//
//	int halfFilterSize = filterSize / 2;
//
//	for (int i = halfFilterSize; i < height - halfFilterSize; i++) {
//		for (int j = halfFilterSize; j < width - halfFilterSize; j++) {
//			unsigned char* redValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			unsigned char* greenValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			unsigned char* blueValues = malloc(filterSize * filterSize * sizeof(unsigned char));
//			int index = 0;
//			for (int k = -halfFilterSize; k <= halfFilterSize; k++) {
//				for (int l = -halfFilterSize; l <= halfFilterSize; l++) {
//					int x = j + l;
//					int y = i + k;
//					if (y >= 0 && y < height && x >= 0 && x < width && index >= 0 && index < filterSize * filterSize) {
//						int pixelIndex = y * width + x;
//						redValues[index] = bmpFile->array[pixelIndex].red;
//						greenValues[index] = bmpFile->array[pixelIndex].green;
//						blueValues[index] = bmpFile->array[pixelIndex].blue;
//					}
//					index++;
//				}
//			}
//			qsort(redValues, index, sizeof(unsigned char), compare);
//			qsort(greenValues, index, sizeof(unsigned char), compare);
//			qsort(blueValues, index, sizeof(unsigned char), compare);
//			int pixelIndex = i * width + j;
//			bmpFile->array[pixelIndex].red = redValues[index / 2];
//			bmpFile->array[pixelIndex].green = greenValues[index / 2];
//			bmpFile->array[pixelIndex].blue = blueValues[index / 2];
//			free(redValues);
//			free(greenValues);
//			free(blueValues);
//		}
//	}
//
//	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
//	fwrite(newPixe, sizeof(Pixel), width * height, *newFile);
//
//	//for (int i = 0; i < height; i++) {
//	//	for (int j = 0; j < width; j++) {
//	//		int pixelIndex = i * width + j;
//	//		unsigned char byte0 = newPixels[pixelIndex].blue;
//	//		unsigned char byte1 = newPixels[pixelIndex].green;
//	//		unsigned char byte2 = newPixels[pixelIndex].red;
//	//		fwrite(&byte0, sizeof(Pixel), 1, *newFile);
//	//		fwrite(&byte1, sizeof(Pixel), 1, *newFile);
//	//		fwrite(&byte2, sizeof(Pixel), 1, *newFile);
//	//	}
//	//}
//
//
//	//for (int i = 0; i < bmpFile->dhdr.sizeData; i++) {
//	//	unsigned char byte0 = newPixels[i].blue;
//	//	unsigned char byte1 = newPixels[i].green;
//	//	unsigned char byte2 = newPixels[i].red;
//	//	fwrite(&byte0, sizeof(unsigned char), 1, *newFile);
//	//	fwrite(&byte1, sizeof(unsigned char), 1, *newFile);
//	//	fwrite(&byte2, sizeof(unsigned char), 1, *newFile);
//	//	
//	//}
//	//free(newPixels);
//	fclose(*newFile);
//}

void medianFilter(BMPFile* bmpFile, FILE** newFile, char* fileName, int filterSize) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	Pixel* pixels = (Pixel*)malloc(height * width * sizeof(Pixel));
	fread(pixels, sizeof(Pixel), height * width, *newFile);

	Pixel* newPixels = (Pixel*)malloc(height * width * sizeof(Pixel));
	memcpy(newPixels, pixels, height * width * sizeof(Pixel));

	int halfFilterSize = filterSize / 2;

	for (int i = halfFilterSize; i < height - halfFilterSize; i++) {
		for (int j = halfFilterSize; j < width - halfFilterSize; j++) {
			unsigned char* redValues = malloc(filterSize * filterSize * sizeof(unsigned char));
			unsigned char* greenValues = malloc(filterSize * filterSize * sizeof(unsigned char));
			unsigned char* blueValues = malloc(filterSize * filterSize * sizeof(unsigned char));
			int index = 0;
			for (int k = -halfFilterSize; k <= halfFilterSize; k++) {
				for (int l = -halfFilterSize; l <= halfFilterSize; l++) {
					int x = j + k;
					int y = i + l;
					if (y >= 0 && y < height && x >= 0 && x < width && index >= 0 && index < filterSize * filterSize) {
						int pixelIndex = y * width + x;
						redValues[index] = pixels[pixelIndex].red;
						greenValues[index] = pixels[pixelIndex].green;
						blueValues[index] = pixels[pixelIndex].blue;
					}
					index++;
				}
			}
			qsort(redValues, index, sizeof(unsigned char), compare);
			qsort(greenValues, index, sizeof(unsigned char), compare);
			qsort(blueValues, index, sizeof(unsigned char), compare);
			int medianIndex = index / 2;
			int newPixelIndex = i * width + j;
			newPixels[newPixelIndex].red = redValues[medianIndex];
			newPixels[newPixelIndex].green = greenValues[medianIndex];
			newPixels[newPixelIndex].blue = blueValues[medianIndex];
			free(redValues);
			free(greenValues);
			free(blueValues);
		}
	}
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fwrite(newPixels, sizeof(Pixel), height * width, *newFile);

	free(pixels);
	free(newPixels);

}
