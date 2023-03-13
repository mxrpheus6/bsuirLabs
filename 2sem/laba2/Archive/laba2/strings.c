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

char convertUpperChar(char symbol) {
	if (symbol > 64 && symbol < 91) {
		symbol += 32;
	}
	return symbol;
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