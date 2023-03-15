#include <stdio.h>
#include <stdlib.h>


#include "menu.h"
#include "structeres.h"
#include "archive.h"
#include "comparators.h"
#include "files.h"
#include "stack.h"

void mainMenu(struct StackNode* topOfStack, struct WordFrequency* words, struct Dictionary* changes, FILE* pointerOg, int* sizeOfArray, int* sizeOfDict) {
	FILE* pointerArch;
	initStackFromFile(&topOfStack, pointerOg);
	printStack(topOfStack);
	printf("\nPress any button 'Enter' to continue");
	getchar();
	system("cls");
	stackToArray(&topOfStack, &words, sizeOfArray);
	printf("Stack placed into array and deleted.\nNow we fill dictionary");
	printf("\n\nPress button 'Enter' to continue");
	getchar();
	qsort(words, *sizeOfArray, sizeof(WordFrequency), compareSize);
	fillDictionaryArray(&words, pointerOg, &changes, *sizeOfArray, sizeOfDict);
	pushDictionaryToFile(&changes, &pointerArch, *sizeOfDict);
	archiveFile(pointerOg, pointerArch, &changes, sizeOfDict);
	//fclose(pointerArch);
}