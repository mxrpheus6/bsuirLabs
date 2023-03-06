#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

StackNode* pushStackNode(StackNode* topOfStack) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->word = NULL;
	temp->data = NULL;
	temp->nextElement = topOfStack;
	return temp;
}

StackNode* popStackNode(StackNode* topOfStack) {
	if (!topOfStack) return NULL;
	if (topOfStack->word)
		free(topOfStack->word);
	if (topOfStack->data)
		free(topOfStack->data);
	StackNode* temp = topOfStack->nextElement; //преже чем удалять узел нам нужно узнать какой идет поле него
	free(topOfStack);
	return temp;
}

void freeStack(StackNode* topOfStack) {
	while (topOfStack)
		popStackNode(topOfStack);
}

void setStackNodeWord(StackNode* topOfStack, char* word) {
	if (topOfStack->word)
		free(topOfStack->word);
	topOfStack->word = (char*)malloc(strlen(word) + 1);
	strcpy(topOfStack->word, word);
}

void setStackNodeData(StackNode* topOfStack, void* data, size_t size) {
	if (topOfStack->data)
		free(topOfStack->data);
	topOfStack = malloc(size);
	memcpy(topOfStack->data, data, size); //копируем блок данных в память по указателю data, берем из void* data 
}