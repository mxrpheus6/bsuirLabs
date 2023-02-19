#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "strings.h"

void charMemoryAllocate(char** string) {
	*string = (char*)malloc(255 * sizeof(char));
}

void charMemoryRelocate(char** string) {
	int len = strlen_n(*string);
	*string = (char*)realloc(*string, len);
	(*string)[len - 1] = '\0';
}
