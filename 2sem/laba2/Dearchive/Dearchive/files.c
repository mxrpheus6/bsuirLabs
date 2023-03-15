#include <stdio.h>
#include <stdlib.h>

#include "files.h"

void fileOpen(FILE** pointer) {
	*pointer = fopen("D:/Work/archive/archivedText.txt", "r+");
	if (*pointer == NULL) {
		printf("Error! Cannot open file.");
		exit(1);
	}
	printf("Success!");
	Sleep(2000);
}

void fileCreate(FILE** pointer) {
	*pointer = fopen("D:/Work/archive/dearchivedText.txt", "w+");
	if (*pointer == NULL) {
		printf("Unknown error happend. Please try again...");
		exit(1);
	}
	printf("Success!");
}