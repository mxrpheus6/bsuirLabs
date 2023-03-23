#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "bmpReader.h"

BMPFile* loadBMPFile(char* fileName) {
	FILE* filePointer = fopen(fileName, "rb");
	if (!filePointer) {
		printf("Can't load file %s", fileName);
		exit(1);
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
	//for (int row = 0; row < height; row++) {
	//	for (int col = 0; col < width; col++) {
	//		int index = (row * width + col) * bytesPerPixel;
	//		bmpFile->array[row * width + col].blue = bmpFile->data[index];
	//		bmpFile->array[row * width + col].green = bmpFile->data[index + 1];
	//		bmpFile->array[row * width + col].red = bmpFile->data[index + 2];
	//		bmpFile->array[row * width + col].alpha = (alphaChannel ? bmpFile->data[index + 3] : 0);
	//	}
	//}
	int j = 0;
	for (int i = 0; i < height * width * bytesPerPixel; i += bytesPerPixel) {
		bmpFile->array[j].blue = bmpFile->data[i];
		bmpFile->array[j].green = bmpFile->data[i+ 1];
		bmpFile->array[j].red = bmpFile->data[i + 2];
		if (alphaChannel)
			bmpFile->array[j].alpha = bmpFile->data[i + 3];
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

void createCopy(BMPFile* bmpFile, FILE** newFile) {
	*newFile = fopen("obj/new.bmp", "w+b");
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
		if (alphaChannel)
			bmpFile->array[i].alpha = bmpFile->data[i + 3];
		fwrite(&bmpFile->array[i].blue, sizeof(unsigned char), 1, *newFile);
		fwrite(&bmpFile->array[i].green, sizeof(unsigned char), 1, *newFile);
		fwrite(&bmpFile->array[i].red, sizeof(unsigned char), 1, *newFile);
		if (alphaChannel) {
			fwrite(&bmpFile->array[i].alpha, sizeof(unsigned char), 1, *newFile);
		}
	}
}

//void createNegativeImage(BMPFile* bmpFile, FILE** newFile) {
//	createCopy(bmpFile, newFile);
//	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
//	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
//	int width = bmpFile->dhdr.width;
//	int height = bmpFile->dhdr.height;
//
//	int alphaChannel = (bytesPerPixel == 4);
//
//	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
//		unsigned char byte0 = 255 - bmpFile->data[i];
//		unsigned char byte1 = 255 - bmpFile->data[i + 1];
//		unsigned char byte2 = 255 - bmpFile->data[i + 2];
//		unsigned char byte3 = 255;
//		fwrite(&byte0, sizeof(unsigned char), 1, *newFile);
//		fwrite(&byte1, sizeof(unsigned char), 1, *newFile);
//		fwrite(&byte2, sizeof(unsigned char), 1, *newFile);
//		if (alphaChannel)
//			fwrite(&byte3, sizeof(unsigned char), 1, *newFile);
//	}
//}

void createNegativeImage(BMPFile* bmpFile, FILE** newFile) {
	createCopy(bmpFile, newFile);
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

}

void createBWImage(BMPFile* bmpFile, FILE** newFile) {
	createCopy(bmpFile, newFile);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	int alphaChannel = (bytesPerPixel == 4);

	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		unsigned char byte0 = bmpFile->array[i].blue;
		unsigned char byte1 = bmpFile->array[i].green;
		unsigned char byte2 = bmpFile->array[i].red;
		unsigned char byte3 = 255;
		char gray = (0.3 * byte2 + byte1 * 0.59 + byte0 * 0.11);
		fwrite(&gray, sizeof(unsigned char), 1, *newFile);
		fwrite(&gray, sizeof(unsigned char), 1, *newFile);
		fwrite(&gray, sizeof(unsigned char), 1, *newFile);
		if (alphaChannel)
			fwrite(&gray, sizeof(unsigned char), 1, *newFile);
	}
}

void GammaCorrection(BMPFile* bmpFile, FILE** newFile, float gamma) {
	createCopy(bmpFile, newFile);
	fseek(*newFile, bmpFile->bhdr.pixelOffset, SEEK_SET);
	int bytesPerPixel = bmpFile->dhdr.bitsPerPixel / 8;
	int width = bmpFile->dhdr.width;
	int height = bmpFile->dhdr.height;

	int alphaChannel = (bytesPerPixel == 4);

	for (int i = 0; i < bmpFile->dhdr.sizeData; i += bytesPerPixel) {
		float blue = (float)bmpFile->array[i].blue / 255.0;
		float green = (float)bmpFile->array[i].green / 255.0;
		float red = (float)bmpFile->array[i].red / 255.0;
		float alpha = (float)bmpFile->array[i].alpha / 255.0;

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
		if (alphaChannel)
			fwrite(&alpha, sizeof(unsigned char), 1, *newFile);
	}
}