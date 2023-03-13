#include <stdio.h>

#include "structeres.h"

void printStructArray(WordFrequency* array, int size) {
	for (int i = 0; i < size; i++) {
		printf("Word: %s\t", array[i].word);
		//printf("Freq: %d\n", array[i].frequency);
		printf("Length: %d\t", array[i].length);
		printf("Size: %d\t\n", array[i].size);
	}
	/*for (int i = 6700; i < size; i++) {
		printf("Word: %s\n", array[i].word);
		printf("Freq: %d\n", array[i].frequency);
		printf("Length: %d\n", array[i].length);
		printf("Size: %d\n\n", array[i].size);
	}*/
}

void printDictionary(Dictionary* array, int size) {
	for (int i = 0; i < size; i++) {
		printf("Og Word: %s\t||\tChanged Word: %s\n", array[i].originalWord, array[i].changeWord);
	}
}