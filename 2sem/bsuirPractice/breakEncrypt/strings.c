#include "strings.h"

int isLetter(char symbol) {
	if (symbol >= 'a' && symbol <= 'z' || symbol >= 'A' && symbol <= 'Z')
		return TRUE;

	return FALSE;
}

void upperToLower(char* symbol) {
	if (*symbol >= 'A' && *symbol <= 'Z') {
		*symbol += 32;
	}
}

void freqAnalysis(FreqDict** array, char** path) {
	FILE* pointer;
	char symbol;

	*path = openByPath(&pointer);

	while ((symbol = fgetc(pointer)) != EOF) {
		if (isLetter(symbol) == TRUE) {
			upperToLower(&symbol);
			(*array)[symbol - 'a'].frequency++;
		}
	}

	fclose(pointer);
}

void caesaerCipher(char* text, int shift, int mode) {
	int i = 0;
	char currentChar;

	while (text[i] != '\0' && text[i] != '\n') {
		currentChar = text[i];

		if (isLetter(currentChar) == FALSE) {
			text[i] = currentChar;
			i++;
			continue;
		}

		if (currentChar >= 'A' && currentChar <= 'Z') {
			currentChar = currentChar + (shift * mode);

			if (currentChar < 'A')
				currentChar = currentChar + ALPHABET_SIZE;
			else if (currentChar > 'Z')
				currentChar = currentChar - ALPHABET_SIZE;
		}

		if (currentChar >= 'a' && currentChar <= 'z') {
			currentChar = currentChar + (shift * mode);

			if (currentChar < 'a')
				currentChar = currentChar + ALPHABET_SIZE;
			else if (currentChar > 'z')
				currentChar = currentChar - ALPHABET_SIZE;
		}

		text[i] = currentChar;
		i++;
	}
}