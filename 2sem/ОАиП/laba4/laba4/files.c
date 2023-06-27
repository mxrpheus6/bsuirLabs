#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logs.h"
#include "files.h"

int openFile(FILE** fp, char* fileName, const char* access, FILE* logPointer) {
	if (strstr(fileName, ".txt") == NULL) {
		createMessage(&logPointer, "[WARN] User entered invalid file format");
		printf("Error. Incorrect file format. Try again.\nPlease, enter correct path: ");
		return 1;
	}
	*fp = fopen(fileName, access);
	if (*fp == NULL) {
		createMessage(&logPointer, "[ERROR] User entered invalid file path");
		printf("Error. Can't reach file %s\nPlease, enter correct path: ", fileName);
		return 1;
	}
	return 0;
}

void getPath(FILE** fp, char* fileName, char* access, FILE* logPointer) {
	printf("Enter path with file name: ");
	getString(fileName);
	while (openFile(fp, fileName, access, logPointer) != 0) {
		fgets(fileName, 256, stdin);
		fileName[strlen(fileName) - 1] = '\0';
	}
}