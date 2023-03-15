#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "structures.h"
#include "dearchive.h"

int main(void) {
	FILE* pointerArch;
	FILE* pointerNew;
	Dictionary* array = NULL;
	int size = 0;
	fileOpen(&pointerArch);
	fileCreate(&pointerNew);
	fillDictionaryFromFile(pointerArch, &array, &size);
	dearchiveFile(pointerArch, pointerNew, &array, &size);
	return 0;
}