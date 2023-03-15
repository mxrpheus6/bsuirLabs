#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "structures.h"

void allocateDictArray(struct Dictionary** array, int size) {
	if (*array == NULL) 
		*array = (Dictionary*)malloc(size * sizeof(Dictionary));
	else
		*array = (Dictionary*)realloc(*array, size * sizeof(Dictionary));
}