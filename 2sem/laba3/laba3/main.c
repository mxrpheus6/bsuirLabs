#include <stdio.h>
#include <stdlib.h>

#include "bmpReader.h"
#include "menu.h"

int main(void) {
	char path[256];
	FILE* newFile;
	float gamma;
	int window;
	/*printf(
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
		bmpf->dhdr.colorsImp);*/
	mainMenu(path, &newFile, &gamma, &window);
	return 0;
}