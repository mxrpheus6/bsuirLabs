#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

int stringLength(const char* string) {
	int i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}

void getString(char** string) {

	char chr;
	int i = 0;
	while ((chr = getchar()) != EOF && chr != '\n') {
		(*string)[i++] = chr;
		if (i == 255) {
			(*string) = (char*)realloc((*string), (i * 2) * sizeof(char));
		}
	}
	(*string) = (char*)realloc((*string), (i + 1) * sizeof(char));
	(*string)[i] = '\0';
}

void stringRemoveTrailingSpaces(char** string) {
	int strLen = stringLength((*string));
	int j;
	int k;
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
		if ((*string)[0] == ' ') {
			for (k = 0; k < strLen - 1; k++) {
				(*string)[k] = (*string)[k + 1];
			}
			(*string)[k] = '\0';
			strLen--;
			if ((*string)[strLen - 1] == ' ') {
				for (int l = strLen - 1; l > 0; l--) {
					if ((*string)[l - 1] != ' ') {
						(*string)[l] = '\0';
						strLen--;
						break;
					}
					else {
						(*string)[l - 1] = (*string)[l];
						(*string)[l] = '\0';
						strLen--;
					}
				}
			}
		}
	}
	if (strLen > 0) {
		(*string) = (char*)realloc((*string), strLen + 1);
	}
}

void stringRemoveWord(char** string, int k) {
	int strLen = stringLength((*string)) + 1;
	int wordLen = 0;
	(*string)[strLen] = '\0';
	(*string)[strLen - 1] = ' ';
	for (int i = 0; i < strLen; i++) {
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
		strLen--;
	}
	if (strLen > 0) {
		(*string) = (char*)realloc((*string), strLen + 1);
	}
}

void findDeleteSubstring(char** string1, char** string2) {
	int strLen1 = stringLength(*string1);
	int strLen2 = stringLength(*string2);
	int temp = strLen1 - strLen2;
	int m;
	int flag;
	for (int i = 0; i < strLen1; i++) {
		flag = 0;
		if ((*string1)[i] == (*string2)[0]) {
			int k = 0;
			int border = i + strLen2;
			for (int j = i; j < border; j++) {
				if ((*string1)[j] != (*string2)[k]) {
					flag = 1;
					break;
				}
				k++;
			}
			if (flag == 0) {
				for (int l = i; l < l + strLen2; l++)
				{
					for (m = l; m < strLen1 - 1; m++)
					{
						(*string1)[m] = (*string1)[m + 1];
					}
					(*string1)[m] = '\0';
					l--;
					strLen1--;
					if (strLen1 == temp) {
						break;
					}
				}
			}
			
		}
		if (strLen1 == temp) {
			break;
		}
		if (strLen1 > 0) {
			(*string1) = (char*)realloc((*string1), strLen1 + 1);
		}
	}
}