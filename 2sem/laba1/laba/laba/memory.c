#include <stdlib.h>
#include <string.h>

#include "memory.h"

void charMemoryAllocate(char** string) {
	*string = (char*)malloc(255 * sizeof(char));
}

void charMemoryRelocate(char** string) {
	int len = strlen(*string);
	*string = (char*)realloc(*string, strlen(*string));
	(*string)[len - 1] = '\0';
}
