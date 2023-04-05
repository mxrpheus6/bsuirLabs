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
	
	if (bmpFile->dhdr.bitsPerPixel != 24) {
		printf("Invalid bits. Programm supports only 24 bit images.\nPlease, enter other path: ", fileName);
		free(bmpFile);
		return 2;
	}

	bmpFile->data = (unsigned char*)malloc(bmpFile->dhdr.sizeData);
	fseek(filePointer, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fread(bmpFile->data, bmpFile->dhdr.sizeData, 1, filePointer);
	
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	bmpFile->array = (Pixel*)malloc(width * height * sizeof(Pixel));

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

void printBMP(BMPFile* bmpf) {
	printf(
		"ID:%c%c\n"
		"size:%d\n"
		"pixel offset:%d\n"
		"sizeOfHeader: %d\n"
		"width: %d\n"
		"height: %d\n"
		"colorPlanes: %d\n"
		"bitsPerPixel: %d\n"
		"comprassionMethod: %d\n"
		"sizeData: %d\n"
		"pWidth: %d\n"
		"pHeight: %d\n"
		"colorsCount: %d\n"
		"colorsImp: %d\n",
		bmpf->bhdr.ID[0],
		bmpf->bhdr.ID[1],
		bmpf->bhdr.sizeOfFile,
		bmpf->bhdr.pixelOffset,
		bmpf->dhdr.sizeOfHeader,
		bmpf->dhdr.width,
		bmpf->dhdr.height,
		bmpf->dhdr.colorPlanes,
		bmpf->dhdr.bitsPerPixel,
		bmpf->dhdr.compressionMethod,
		bmpf->dhdr.sizeData,
		bmpf->dhdr.pWidth,
		bmpf->dhdr.pHeight,
		bmpf->dhdr.colorsCount,
		bmpf->dhdr.colorsImp);
}

void createCopy(BMPFile* bmpFile, FILE** newFile, char* fileName) {
	*newFile = fopen(fileName, "w+b");
	fwrite(&bmpFile->bhdr, sizeof(BITMAPFILEHEADER), 1, *newFile);
	fwrite(&bmpFile->dhdr, sizeof(BITMAPINFOHEADER), 1, *newFile);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fwrite(bmpFile->data, bmpFile->dhdr.sizeData, 1, *newFile);

	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;

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

	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		unsigned char byte0 = 255 - bmpFile->array[i].blue;
		unsigned char byte1 = 255 - bmpFile->array[i].green;
		unsigned char byte2 = 255 - bmpFile->array[i].red;
		fwrite(&byte0, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte1, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte2, sizeof(unsigned char), 1, *newFile);
	}
	fclose(*newFile);
}

void createBWImage(BMPFile* bmpFile, FILE** newFile, char* fileName) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;

	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		unsigned char byte = (bmpFile->array[i].blue * 0.11 + bmpFile->array[i].red * 0.3 + bmpFile->array[i].green * 0.59);
		fwrite(&byte, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte, sizeof(unsigned char), 1, *newFile);
		fwrite(&byte, sizeof(unsigned char), 1, *newFile);
	}
	fclose(*newFile);
}

void GammaCorrection(BMPFile* bmpFile, FILE** newFile, float gamma, char* fileName) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;

	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		float blue = (float)bmpFile->array[i].blue / 255.0;
		float green = (float)bmpFile->array[i].green / 255.0;
		float red = (float)bmpFile->array[i].red / 255.0;

		blue = (powf(blue, 1.0 / gamma) * 255.0);
		green = (powf(green, 1.0 / gamma) * 255.0);
		red = (powf(red, 1.0 / gamma) * 255.0);

		unsigned char b;
		unsigned char g;
		unsigned char r;
		b = blue;
		g = green;
		r = red;

		fwrite(&b, sizeof(unsigned char), 1, *newFile);
		fwrite(&g, sizeof(unsigned char), 1, *newFile);
		fwrite(&r, sizeof(unsigned char), 1, *newFile);
	}
	fclose(*newFile);
}

void medianFilter(BMPFile* bmpFile, FILE** newFile, char* fileName, int sizeOfWindow) {
	createCopy(bmpFile, newFile, fileName);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;
	int halfWindow = sizeOfWindow / 2;
	int x;
	int y;
	int medianIndex;
	int newPixelIndex;
	unsigned char* redPixels = malloc(sizeOfWindow * sizeOfWindow);
	unsigned char* greenPixels = malloc(sizeOfWindow * sizeOfWindow);
	unsigned char* bluePixels = malloc(sizeOfWindow * sizeOfWindow);

	Pixel* pixels = (Pixel*)malloc(height * width * sizeof(Pixel));
	memcpy(pixels, bmpFile->data, height * width * sizeof(Pixel));
	Pixel* newPixels = (Pixel*)malloc(height * width * sizeof(Pixel));
	memcpy(newPixels, pixels, height * width * sizeof(Pixel));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i >= halfWindow && i < height - halfWindow && j >= halfWindow && j < width - halfWindow) {
				int index = 0;
				for (int k = -halfWindow; k <= halfWindow; k++) {
					for (int l = -halfWindow; l <= halfWindow; l++) {
						x = j + k;
						y = i + l;
						if ((y >= 0 && y < height && x >= 0 && x < width) && index >= 0 && index < sizeOfWindow * sizeOfWindow) {
							int pixelIndex = y * width + x;
							bluePixels[index] = pixels[pixelIndex].blue;
							greenPixels[index] = pixels[pixelIndex].green;
							redPixels[index] = pixels[pixelIndex].red;
						}
						index++;
					}
				}
				qsort(redPixels, index, sizeof(unsigned char), compare);
				qsort(greenPixels, index, sizeof(unsigned char), compare);
				qsort(bluePixels, index, sizeof(unsigned char), compare);
				medianIndex = index / 2;
				newPixelIndex = i * width + j;
				newPixels[newPixelIndex].blue = bluePixels[medianIndex];
				newPixels[newPixelIndex].green = greenPixels[medianIndex];
				newPixels[newPixelIndex].red = redPixels[medianIndex];
			}
		}
	}
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	fwrite(newPixels, sizeof(Pixel), height * width, *newFile);

	free(pixels);
	free(newPixels);
	free(bluePixels);
	free(greenPixels);
	free(redPixels);
	fclose(*newFile);
}