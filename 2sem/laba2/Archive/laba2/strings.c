#include <stdlib.h>
#include <string.h>

#include "structeres.h"

int isLetter(char symbol) {
	if ((symbol > 64 && symbol < 91 || symbol > 96 && symbol < 123)) {
		return TRUE;
	}
	return FALSE;
}

int isWord(char* string) {
	int i = 0;
	while (string[i] != '\n' && string[i] != '\0') {
		if (isLetter(string[i]) == FALSE) {
			return FALSE;
		}
		i++;
	}
	return TRUE;
}


int stringASCII(char* string) {
	int i = 0;
	while (string[i] != '\0') {
		if ((!(string[i] >= 97 && string[i] <= 122) && !(string[i] >= 65 && string[i] <= 90)))
			return 0;
		i++;
	}
	return i;
}

int charASCII(char symbol) {
	if (((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')))
		return TRUE;
	return FALSE;
}

int deliCheck(char symbol) {
	char delimiters[] = " ()-,.?!;:'\" \n";
	int i = 0;
	while (delimiters[i] != '\0') {
		if (symbol == delimiters[i])
			return FALSE;
		i++;
	}
	return TRUE;
}

int wordIndex(const char* string, int* index) {
	while (string[(*index)] != '\0') {
		if ((*index) == 0) {
			if (charASCII(string[(*index)]) != FALSE) {
				return (*index);
			}
		}
		else if ((*index) > 0) {
			if (string[(*index) - 1] != '-' && charASCII(string[(*index) - 1]) == FALSE && charASCII(string[(*index)]) != FALSE) {
				return (*index);
			}
		}
		(*index)++;
	}
	return -1;
}

char* getWordFromTxt(const char* string, int beginIndex) {
	int i = 0;
	char* word = (char*)malloc(256);
	while (deliCheck(string[beginIndex]) != FALSE) {
		word[i] = string[beginIndex];
		beginIndex++;
		i++;
	}
	word = (char*)realloc(word, strlen(word) + 1);
	word[i] = '\0';
	return word;
}

char* getChangeForWord(struct Dictionary** array, const char* string, const int* size) {
	char* changedWord = NULL;
	int len;
	for (int i = 0; i < *size; i++) {
		if (strcmp(string, (*array)[i].originalWord) == 0) {
			len = strlen((*array)[i].changeWord);
			changedWord = (char*)malloc(len + 1);
			strcpy(changedWord, (*array)[i].changeWord);
			break;
		}
		if (strcmp(string, (*array)[i].changeWord) == 0) {
			len = strlen((*array)[i].originalWord);
			changedWord = (char*)malloc(len + 1);
			strcpy(changedWord, (*array)[i].originalWord);
			break;
		}
	}
	return changedWord;
}