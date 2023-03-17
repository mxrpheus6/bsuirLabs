#include <stdio.h>
#include <Windows.h>

#include "files.h"

void fileOpen(FILE** pointer) {
	*pointer = fopen("D:/Work/archive/test.txt", "r+");
	if (*pointer == NULL) {
		printf("Error! Cannot open file.");
		exit(1);
	}
	printf("Success!");
}

void fileCreate(FILE** pointer) {
	*pointer = fopen("D:/Work/archive/archivedText.txt", "w+");
	if (*pointer == NULL) {
		printf("Unknown error happend. Please try again...");
		exit(1);
	}
}

void fileReOpen(FILE** pointer) {
	*pointer = fopen("D:/Work/archive/archivedText.txt", "a+");
	if (*pointer == NULL) {
		printf("Unknown error happend. Please try again...");
		exit(1);
	}
}
