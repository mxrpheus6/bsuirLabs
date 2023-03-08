#include <stdio.h>

#include "strings.h"
#include "structeres.h"
#include "stack.h"
#include "files.h"

int main(void) {
	StackNode* topOfStack = NULL;
	WordFreauency* words = NULL;
	FILE* filePointer;
	int sizeOfArray = 0;
	fileOpen(&filePointer);
	initStackFromFile(&topOfStack, filePointer);
	printStack(topOfStack);
	return 0;
}