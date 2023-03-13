#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structeres.h"
#include "archive.h"
#include "files.h"
#include "strings.h"

void fillDictionaryArray(struct WordFrequency** arrayOfWords, FILE* pointer, struct Dictionary** arrayOfChanges, int amountOfWords, int* sizeOfDictionary) {
	int beginIndex = 0;
	int endIndex = amountOfWords - 1;
	int i = 0;
	int len;
	while ((strlen((*arrayOfWords)[endIndex].word) <= 4)) {
		if (strlen((*arrayOfWords)[beginIndex].word) <= strlen((*arrayOfWords)[endIndex].word))
			free((*arrayOfWords)[beginIndex].word);
			beginIndex++;
		while ((strlen((*arrayOfWords)[beginIndex].word) > strlen((*arrayOfWords)[endIndex].word))) {
			if ((*arrayOfWords)[beginIndex].size > (*arrayOfWords)[endIndex].size) {
				(*sizeOfDictionary)++;
				if ((*arrayOfChanges) == NULL)
					(*arrayOfChanges) = (Dictionary*)malloc(*sizeOfDictionary * sizeof(Dictionary));
				else
					(*arrayOfChanges) = (Dictionary*)realloc(*arrayOfChanges, *sizeOfDictionary * sizeof(Dictionary));
				len = strlen((*arrayOfWords)[beginIndex].word);
				(*arrayOfChanges)[i].originalWord = (char*)malloc(len + 1);
				strcpy((*arrayOfChanges)[i].originalWord, (*arrayOfWords)[beginIndex].word);
				len = strlen((*arrayOfWords)[endIndex].word);
				(*arrayOfChanges)[i].changeWord = (char*)malloc(len + 1);
				strcpy((*arrayOfChanges)[i].changeWord, (*arrayOfWords)[endIndex].word);
				free((*arrayOfWords)[beginIndex].word);
				free((*arrayOfWords)[endIndex].word);
				beginIndex++;
				endIndex--;
				i++;
			}
		}
	}
	free(*arrayOfWords);
}

void pushDictionaryToFile(struct Dictionary** arrayOfChanges, FILE** pointer, int sizeOfDictionary) {
	fileCreate(pointer);
	for (int i = 0; i < sizeOfDictionary; i++) {
		fprintf(*pointer, "%s", (*arrayOfChanges)[i].originalWord);
		fprintf(*pointer, "%s", "|");
		fprintf(*pointer, "%s", (*arrayOfChanges)[i].changeWord);
		fprintf(*pointer, "%c", '\n');
	 }
	fprintf(*pointer, "%s", "&\n");
}

void archiveFile(FILE* pointerOg, FILE* pointerArch, Dictionary* array, int sizeOfDictionary) {
	int i;
	int len;
	char bufFromFile[4096];
	char delimiters[] = "()-,.?!;:'\" ";
	char* word = (char*)malloc(1000);
	char temp = '\0';
	char* pch;
	int flag = 1;
	fileReOpen(&pointerArch);
	fseek(pointerOg, 0, 0);
	fseek(pointerArch, 0L, SEEK_END);
	while (fgets(bufFromFile, 4096, pointerOg) != NULL && !feof(pointerOg)) {
		pch = strtok(bufFromFile, " ");
		while (pch != NULL) {
			word = NULL;
			len = strlen(pch);
			if (deliCheck(pch[len]) == FALSE) {
				temp = pch[len];
				pch[len] = '\0';
			}
			if (pch[len - 1] == '\n') {
				pch[len - 1] = '\0';
			}
			for (i = 0; i < sizeOfDictionary; i++) {
				if (strcmp(array[i].originalWord, pch) == 0) {
					word = NULL;
					fprintf(pointerArch, "%s", array[i].changeWord);
					if (deliCheck(temp) == FALSE) {
						fprintf(pointerArch, "%c", temp);
					}
					else 
					{
						fprintf(pointerArch, "%c", ' ');
					}
					break;
				}
				else {
					word = pch;
				}
			}
			if (word != NULL) {
				fprintf(pointerArch, "%s", word);
				if (deliCheck(temp) == FALSE) {
					fprintf(pointerArch, "%c", temp);
				}
				else {
					fprintf(pointerArch, "%c", ' ');
				}
			}
			pch = strtok(NULL, " ");
		}
		fprintf(pointerArch, "%c", '\n');
	}
}