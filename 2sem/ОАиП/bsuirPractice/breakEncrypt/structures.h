#pragma once

#define ALPHABET_SIZE 26

typedef struct FreqDict {
	char symbol;
	int frequency;
}FreqDict;

typedef enum caesarMode {
	ENCRYPT = 1,
	DECRYPT = -1
}caesarMode;

void initFreqDict(FreqDict** array);

void nullFreqDict(FreqDict** array);

int compareFreq(const void* a, const void* b);

FreqDict findMostPopular(FreqDict* array);