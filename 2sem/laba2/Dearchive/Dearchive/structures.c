#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "memory.h"

void fillDictionaryFromFile(FILE* pointerArch, Dictionary** array, int* size) {
	char bufFromFile[256];
	char* pointerChar;
	int len;
	int i = 0;
	//(*array) = (Dictionary*)malloc(1000 * sizeof(Dictionary));
	while (1) {
		fgets(bufFromFile, 256, pointerArch);
		if (bufFromFile[0] == '&') {
			break;
		}
		(*size)++;
		allocateDictArray(array, *size);
		pointerChar = strtok(bufFromFile, "|");
		len = strlen(pointerChar);
		(*array)[i].originalWord = (char*)malloc(len + 1);
		strcpy((*array)[i].originalWord, pointerChar);
		pointerChar = strtok(NULL, "|");
		pointerChar[strlen(pointerChar) - 1] = '\0';
		len = strlen(pointerChar);
		(*array)[i].changeWord = (char*)malloc(len + 1);
		strcpy((*array)[i].changeWord, pointerChar);
		i++;
	}
}