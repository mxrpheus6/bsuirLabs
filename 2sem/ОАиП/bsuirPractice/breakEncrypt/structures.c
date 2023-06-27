#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

void nullFreqDict(FreqDict** array) {

	for (int i = 'a'; i <= 'z'; i++) {
		(*array)[i - 'a'].symbol = i;
		(*array)[i - 'a'].frequency = 0;
	}

}

void initFreqDict(FreqDict** array) {
	*array = (FreqDict*)malloc(ALPHABET_SIZE * sizeof(FreqDict));

	if (*array == NULL) {
		printf("Error. Memory allocation failed");
		exit(-1);
	}
	
	nullFreqDict(array);
}

int compareFreq(const void* a, const void* b) {
	const FreqDict* fieldA = (FreqDict*)a;
	const FreqDict* fieldB = (FreqDict*)b;

	return fieldB->frequency - fieldA->frequency;
}

FreqDict findMostPopular(const FreqDict* array) {
	FreqDict temp = array[0];

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (temp.frequency < array[i].frequency)
			temp = array[i];
	}

	return temp;
}