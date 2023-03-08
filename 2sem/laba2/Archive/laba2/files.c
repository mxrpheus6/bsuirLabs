#include <stdio.h>
#include <Windows.h>

#include "files.h"

void fileOpen(FILE** pointer) {
	*pointer = fopen("D:/Work/archive/gray.txt", "r+");
	if (*pointer == NULL) {
		printf("Error! Cannot open file.");
		exit(1);
	}
	printf("Success!");
	Sleep(2000);
}