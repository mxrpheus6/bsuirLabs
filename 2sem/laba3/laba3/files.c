#include <stdio.h>
#include <string.h>

#include "files.h"

int checkNewFile(char* fileName) {
	if (strstr(fileName, ".bmp") == NULL) {
		printf("Can't create file, incorrect format %s", fileName);
		return 1;
	}
	FILE* filePointer = fopen(fileName, "wb");
	if (!filePointer) {
		printf("Can't create file %s", fileName);
		return 1;
	}
	fclose(filePointer);
	return 0;
}

void createNewFile(char* path) {
	printf("Good! Now enter name of the new bmp file: ");
	fgets(path, 256, stdin);
	path[strlen(path) - 1] = '\0';
	while (checkNewFile(path) == 1) {
		fgets(path, 256, stdin);
		path[strlen(path) - 1] = '\0';
	}
}