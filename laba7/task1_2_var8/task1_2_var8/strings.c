#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

void getString(char** string) {

	int chr, i = 0;
	while ((chr = getchar()) != EOF && chr != '\n') {
		(*string)[i++] = chr;
		(*string) = (char*)realloc((*string), (i + 1) * sizeof(char));
	}
	(*string)[i] = '\0';
}

int stringLength(char* string) {
	int i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}

void stringRemoveTrailingSpaces(char** string) {
	int strLen = stringLength((*string));
	int j, k;
	int flag = 0;
	for (int i = 0; i < strLen - 1; i++)
	{
		if ((*string)[i] == ' ' && (*string)[i + 1] == ' ') {
			for (j = i; j < strLen - 1; j++) {
				(*string)[j] = (*string)[j + 1];
			}
			(*string)[j] = '\0';
			strLen--;
			i--;
		}
	}
	if ((*string)[0] == ' ') {
		for (k = 0; k < strLen - 1; k++) {
			(*string)[k] = (*string)[k + 1];
		}
		(*string)[k] = '\0';
		strLen--;
	}
	if ((*string)[strLen - 1] == ' ') {
		int l;
		for (l = strLen - 1; l > 0; l--) {
			if ((*string)[l - 1] != ' ') {
				(*string)[l] = '\0';
				break;
			}
			else {
				(*string)[l - 1] = (*string)[l];
				(*string)[l] = '\0';
			}
			
		}
	}
}

void stringRemoveWord(char** string, int k) {
	int strLen = stringLength((*string)) + 1;
	int i;
	int wordLen = 0;
	(*string)[strLen] = '\0';
	(*string)[strLen - 1] = ' ';
	for (i = 0; i < strLen; i++) {
		if ((*string)[i] == ' ') {
			if (wordLen < k) {
				i -= wordLen;
				for (int j = i; j < strLen - 1; j++) {
					(*string)[j] = (*string)[j + wordLen + 1];
				}
				i--;
				strLen = strLen - wordLen - 1;
			}
			wordLen = -1;
		}
		wordLen++;
	}
	if ((*string)[strLen - 1] = ' ') {
		(*string)[strLen - 1] = '\0';
	}
}