#include <stdio.h>
#include <stdlib.h>

#include "bmpReader.h"
#include "menu.h"

int main(void) {
	char path[256];
	FILE* newFile;
	float gamma;
	int window;
	mainMenu(path, &newFile, &gamma, &window);
	return 0;
}