#include <stdio.h>
#include <stdlib.h>

#include "bmpReader.h"

int main(void) {
	char path[256];
	fgets(path, 256, stdin);
	path[strlen(path) - 1] = '\0';
	BMPFile* bmpf = loadBMPFile(path);
	BMPFile* newbmpf;
	FILE* newFile;
	float gamma;
	printf("ID:%c%c\n", bmpf->bhdr.ID[0], bmpf->bhdr.ID[1]);
	printf("size:%d\n", bmpf->bhdr.sizeOfFile);
	printf("pixel offset:%d\n", bmpf->bhdr.pixelOffset);
	printf(
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
		bmpf->dhdr.sizeOfHeader,
		bmpf->dhdr.width,
		bmpf->dhdr.height,
		bmpf->dhdr.colorPlanes,
		bmpf->dhdr.bitsPerPixel,
		bmpf->dhdr.comprassionMethod,
		bmpf->dhdr.sizeData,
		bmpf->dhdr.pWidth,
		bmpf->dhdr.pHeight,
		bmpf->dhdr.colorsCount,
		bmpf->dhdr.colorsImp);
	//printBMP(bmpf);
	//createCopy(bmpf, &newbmpf, &newFile);
	//createNegativeImage(bmpf, &newFile);
	//createBWImage(bmpf, &newFile);
	scanf_s("%f", &gamma);
	GammaCorrection(bmpf, &newFile, gamma);
	freeBMPFile(bmpf);
	return 0;
}