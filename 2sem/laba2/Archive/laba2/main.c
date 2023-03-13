#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "strings.h"
#include "structeres.h"
#include "stack.h"
#include "files.h"
#include "comparators.h"
#include "archive.h"

int main(void) {
	StackNode* topOfStack = NULL;
	WordFrequency* words = NULL;
	Dictionary* changes = NULL;
	FILE* filePointer;
	FILE* archivedFilePointer;
	int sizeOfArray = 0;
	int sizeOfDictionary = 0;
	fileOpen(&filePointer);
	mainMenu(topOfStack, words, changes, filePointer, &sizeOfArray, &sizeOfDictionary);
	return 0;
}
