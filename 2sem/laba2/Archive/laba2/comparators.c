#include <stdio.h>

#include "comparators.h"
#include "structeres.h"

int compareSize(const void* a, const void* b) {
	const WordFrequency* firstThing = (const WordFrequency*)a;
	const WordFrequency* secondThing = (const WordFrequency*)b;
	if (firstThing->size < secondThing->size) {
		return 1;
	}
	else if (firstThing->size > secondThing->size) {
		return -1;
	}
	else {
		if (firstThing->length < secondThing->length) {
			return 1;
		}
		else if (firstThing->length > secondThing->length) {
			return -1;
		}
		else {
			return 0;
		}
	}
}