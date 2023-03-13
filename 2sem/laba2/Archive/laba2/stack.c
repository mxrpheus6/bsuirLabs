#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "structeres.h"
#include "strings.h"

StackNode* pushStackNode(StackNode* topOfStack) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->name = NULL;
	temp->nextElement = topOfStack;
	return temp;
}

StackNode* popStackNode(StackNode* topOfStack) {
	if (!topOfStack) return NULL;
	if (topOfStack->name)
		free(topOfStack->name);
	StackNode* temp = topOfStack->nextElement; //преже чем удалять узел нам нужно узнать какой идет поле него
	free(topOfStack);
	return temp;
}

void freeStack(StackNode* topOfStack) {
	while (topOfStack)
		topOfStack = popStackNode(topOfStack);
}

void setStackNodeName(StackNode* topOfStack, char* name) {
	if (topOfStack->name)
		free(topOfStack->name);
	topOfStack->name = (char*)malloc(strlen(name) + 1);
	strcpy(topOfStack->name, name);
}

void setStackNodeNum(StackNode* topOfStack, int num) {
	topOfStack->num = num;
}

StackNode* stackCheck(StackNode* topOfStack, char* string) {
	StackNode* currentNode = topOfStack;
	while (currentNode != NULL) {
		if (strcmp(currentNode->name, string) == 0) {
			currentNode->num++;
			return topOfStack;
		}
		currentNode = currentNode->nextElement;
	}
	StackNode* newNode = pushStackNode(topOfStack);
	setStackNodeName(newNode, string);
	setStackNodeNum(newNode, 1);
	return newNode;
}

//void initStackFromFile(StackNode** topOfStack, FILE* pointer) {
//	char bufFromFile[4096];
//	char* temp;
//	int size;
//	int i;
//	int j;
//	while (fgets(bufFromFile, 4096, pointer) != NULL && !feof(pointer)) {
//		i = 0;
//		j = 0;
//		size = 1;
//		temp = (char*)malloc(size);
//		while (bufFromFile[i] != '\n' && bufFromFile[i] != '\0') {
//			if (bufFromFile[i] == ' ' || bufFromFile[i] == '-' || bufFromFile[i] == '.' || bufFromFile[i] == ',' || bufFromFile[i] == '?' || bufFromFile[i] == '!' || bufFromFile[i] == '"' || bufFromFile[i] == '\'' || bufFromFile == ':' || bufFromFile == ';') {
//				temp[j] = '\0';
//				if (strlen(temp) > 1) {
//					*topOfStack = stackCheck(*topOfStack, temp);
//				}
//				i++;
//				j = 0;
//				size = 1;
//				free(temp);
//				temp = (char*)malloc(size);
//			}
//			else {
//				size++;
//				temp[j] = convertUpperChar(bufFromFile[i]);
//				temp = (char*)realloc(temp, size);
//				i++;
//				j++;
//
//			}
//		}
//		if (bufFromFile[i] == '\n') {
//			temp[j] = '\0';
//			if (strlen(temp) > 1 && isWord(temp) == TRUE) {
//				*topOfStack = stackCheck(*topOfStack, temp);
//			}
//			i++;
//			j = 0;
//			size = 1;
//			free(temp);
//			temp = (char*)malloc(size);
//		}
//	}
//}

void initStackFromFile(StackNode** topOfStack, FILE* pointer) {
	char bufFromFile[4096];
	char delimiters[] = "()-,.?!;:'\" \n";
	int counter = 0;
	while (fgets(bufFromFile, 4096, pointer) != NULL && !feof(pointer)) {
		char* pch = strtok(bufFromFile, delimiters);
		while (pch != NULL)
		{
			if (stringASCII(pch) > 1)
				*topOfStack = stackCheck(*topOfStack, pch);
			pch = strtok(NULL, delimiters);
			counter++;
		}
	}
}

void stackToArray(StackNode** topOfStack, WordFrequency** array, int* size) {
	StackNode* currentNode;
	*array = (WordFrequency*)malloc(1 * sizeof(WordFrequency));
	int i = 0;
	int len;
	while (*topOfStack != NULL) {
		currentNode = *topOfStack;
		(*size)++;
		(*array) = (WordFrequency*)realloc((*array), (*size) * sizeof(WordFrequency));
		len = strlen(currentNode->name);
		(*array)[i].word = (char*)malloc(len + 1);
		strcpy((*array)[i].word, currentNode->name);
		(*array)[i].frequency = currentNode->num;
		(*array)[i].length = len;
		(*array)[i].size = currentNode->num * len;
		(*topOfStack) = popStackNode(*topOfStack);
		i++;
	}
}

void printStack(StackNode* topOfStack) {
	StackNode* currentNode = topOfStack;
	printf("Stack contents:\n");
	while (currentNode != NULL) {
		printf("%s: %d\n", currentNode->name, currentNode->num);
		currentNode = currentNode->nextElement;
	}
}