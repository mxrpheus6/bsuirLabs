#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dearchive.h"
#include "structures.h"
#include "strings.h"


void processText(Dictionary** array, int* sizeOfDictionary, char* word, char* bufFromFile, int* beginIndex, char* changedWord, int *index) {
	word = getWordFromTxt(bufFromFile, *beginIndex);
	changedWord = getChangeForWord(array, word, sizeOfDictionary);
	changeWords(&bufFromFile, word, changedWord, index);
	(*index)++;
}

void changeWords(char** buf, const char* word, const char* changedWord, int* index) {
	if (changedWord == NULL) {
		return;
	}
	int count = 0;
	int beginIndex = (*index);
	int tempIndex = 0;
	int difference = strlen(word) - strlen(changedWord);
	if (difference > 0) {
		while (count != strlen(changedWord)) {
			(*buf)[beginIndex] = changedWord[count];
			beginIndex++;
			count++;
		}
		tempIndex = beginIndex;
		for (int i = 0; i < difference; i++) {
			while ((*buf)[beginIndex] != '\0') {
				(*buf)[beginIndex] = (*buf)[beginIndex + 1];
				beginIndex++;
			}
			beginIndex = tempIndex;
		}
		(*index) += strlen(changedWord) - 1;
	}
	else {
		difference = strlen(changedWord) - strlen(word);
		beginIndex = (strlen((*buf)) + 1);
		for (int i = 0; i < difference; i++) {
			while (beginIndex != (*index)) {
				(*buf)[beginIndex] = (*buf)[beginIndex - 1];
				beginIndex--;
			}
			beginIndex = strlen((*buf)) + 1;
		}
		beginIndex = (*index);
		while (count != strlen(changedWord)) {
			(*buf)[beginIndex] = changedWord[count];
			beginIndex++;
			count++;
		}
		(*index) += strlen(changedWord) - 1;
	}
}

void dearchiveFile(FILE* pointerOg, FILE* pointerArch, Dictionary** array, int* sizeOfDictionary) {
	int index = 0;
	int beginIndex = 0;
	char* bufFromFile = (char*)malloc(4096);
	char* word = NULL;
	char* changedWord = NULL;
	fgets(bufFromFile, 4096, pointerOg);
	while (!feof(pointerOg)) {
		while ((beginIndex = wordIndex(bufFromFile, &index)) != -1) {
			processText(array, sizeOfDictionary, word, bufFromFile, &beginIndex, changedWord, &index);
		}
		fprintf(pointerArch, "%s", bufFromFile);
		index = 0;
		fgets(bufFromFile, 4096, pointerOg);
	}
	free(bufFromFile);
	free(word);
	free(changedWord);
	fclose(pointerOg);
	fclose(pointerArch);
}