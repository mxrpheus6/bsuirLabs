#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define TRUE 1
#define FALSE 0

int stringLength(char* string) {
	int i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}

void stringsInput(char*** strings, char** argv, int argc) {
	if (argc == 1) {
		printf("There is no arguments except file name!");
		exit(1);
	}
	(*strings) = (char**)malloc(argc * sizeof(char*));
	for (int i = 1; i < argc; i++) {
		int len = stringLength(argv[i]);
		(*strings)[i - 1] = (char*)calloc(len, sizeof(char*));
		for (int j = 0; j < len; j++) {
			(*strings)[i - 1][j] = argv[i][j];
		}
	}
}

void stringsOutput1(char*** strings, int argc) {
	printf("Strings before sorting:\n");
	for (int i = 0; i < argc - 1; i++) {
		printf("[%d]%s\n", i + 1, (*strings)[i]);
	}
	printf("\n=======================");
}

void stringsOutput2(char*** strings, int*** indexes, int argc) {
	printf("\n\n");
	printf("Strings after sorting:\n");
	for (int i = 0; i < argc - 1; i++) {
		int index = (*indexes)[i][0];
		printf("[%d]%s\n", i + 1, (*strings)[index]);
	}
}

int wordCounter(char*** strings, int index) {
	int counter = 0;
	int symCounter = 0;
	int flag = 0;
	int len = stringLength((*strings)[index]);
	for (int j = 0; j < len; j++) {
		if (j == len - 1 && (*strings)[index][j] != ' ') {
			symCounter++;
			if (symCounter > 0 && symCounter % 2 == 0) {
				counter++;
			}
		}
		if ((*strings)[index][j] != ' ') {
			flag = 1;
		}
		if ((*strings)[index][j] == ' ') {
			if (symCounter > 0 && symCounter % 2 == 0) {
				counter++;
			}
			flag = 0;
			symCounter = 0;
			continue;
		}
		else {
			if (flag == 1) {
				symCounter++;
				continue;
			}
			/*else {
				if (symCounter % 2 == 0) {
					counter++;
				}
				flag = 1;
			}*/
		}
	}
	return counter;
}

int symCounter(char*** strings, int index) {
	int counter = 0;
	int flag = 0;
	int len = stringLength((*strings)[index]);
	for (int j = 0; j < len; j++) {
		if ((*strings)[index][j] == ' ') {
			flag = 0;
			continue;
		}
		else {
			if (flag == 1) {
				counter++;
				continue;
			}
			else {
				flag++;
				counter++;
			}
		}
	}
	return counter;
}

int evenCheck(char*** strings, int index) {
	if (symCounter(&(*strings), index) % 2 == 0) {
		return TRUE;
	}
	return FALSE;
}

void prototype(char*** strings, int*** indexes, int argc) {
	int amountofstrings = argc - 1;
	(*indexes) = (int**)calloc(amountofstrings, sizeof(int*));
	for (int i = 0; i < amountofstrings; i++) {
		(*indexes)[i] = (int*)calloc(2, sizeof(int));
		(*indexes)[i][0] = i;
		(*indexes)[i][1] = wordCounter(&(*strings), i);
	}
}

//void resultArrayOfStrings(char*** strings, int*** indexes, int argc) {
//	int j;
//	int k;
//	int l;
//	for (int i = 0; i < 1; i++) {
//		int index = (*indexes)[i][0];
//		char* temp;
//		temp = (char*)malloc(stringLength((*strings)[i]), sizeof(char));
//		for (j = 0; j < stringLength((*strings)[i]); j++) {
//			temp[j] = (*strings)[i][j];
//		}
//		temp[j] = '\0';
//		(*strings)[i] = (char*)malloc(stringLength((*strings)[index]), sizeof(char));
//		for (k = 0; k < stringLength((*strings)[index]); k++) {
//			(*strings)[i][k] = (*strings)[index][k];
//		}
//		(*strings)[i][k] = '\0';
//		(*strings)[index] = (char*)malloc(stringLength((*strings)[index]), sizeof(char));
//		for (l = 0; l < stringLength((temp)); l++) {
//			(*strings)[index][l] = temp[l];
//		}
//		(*strings)[index][l] = '\0';
//	}
//}
