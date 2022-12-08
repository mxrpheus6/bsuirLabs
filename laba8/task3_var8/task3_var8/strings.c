#include <stdio.h>
#include <stdlib.h>

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

void stringsOutput(char*** strings, int argc) {
	printf("Strings before sorting:\n");
	for (int i = 0; i < argc - 1; i++) {
		printf("[%d]%s\t%d\n", i + 1, (*strings)[i], symCounter(&(*strings), i));
	}
	printf("\nString after sorting:\n");
}

int wordCounter(char*** strings, int index) {
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

//int evenCheck(int*** strings, int index) {
//	if (symCounter(&strings, index) % 2 == 0) {
//		return 0;
//	}
//	return 1;
//}
//
//int evenAmount(int*** strings, int index) {
//	int counter = -1;
//	int len = stringLength((*strings)[index]);
//	for (int i = 0; ; i++)
//	{
//		if (symCounter(&strings, i) % 2 == 0)
//		{
//			counter++;
//			if (counter == len)
//			{
//				return i;
//			}
//		}
//	}
//}

