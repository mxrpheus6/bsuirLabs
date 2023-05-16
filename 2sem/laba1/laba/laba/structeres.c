#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "structeres.h"
#include "memory.h"

void initStruct(Smartphone* pointer) {
	int userInput;
	RamTypes capacity;
	printf("Enter name: ");
	charMemoryAllocate(&pointer->name);
	fgets(pointer->name, 255, stdin);
	charMemoryRelocate(&pointer->name);
	printf("Enter screen size: ");
	while ((scanf_s(" %f", &pointer->screenSize)) != 1 || getchar() != '\n' || pointer->screenSize <= 0) {
		printf("Invalid input. Enter correct screen size: ");
		rewind(stdin);
	}
	printf("Enter RAM (GB): ");
	while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput != 2 && userInput != 4 && userInput != 6 && userInput != 8)) {
		printf("Invalid input. Enter correct RAM: ");
		rewind(stdin);
	}
	capacity = (RamTypes)userInput;
	pointer->ram = capacity;
	printf("Enter memory (GB): ");
	while ((scanf_s(" %d", &pointer->memory)) != 1 || getchar() != '\n' || pointer->memory <= 0) {
		printf("Invalid input. Enter correct memory: ");
		rewind(stdin);
	}
	rewind(stdin);
	printf("Enter battery capacity: ");
	while ((scanf_s(" %d", &pointer->battery)) != 1 || getchar() != '\n' || pointer->battery <= 0) {
		printf("Invalid input. Enter correct battery capacity: ");
		rewind(stdin);
	}
	rewind(stdin);
}

void createStructArr(Smartphone** pointer, int* count) {
	printf("Enter size of array: ");
	while ((scanf_s(" %d", count)) != 1 || getchar() != '\n' || *count <= 0) {
		printf("Invalid input. Enter correct size: ");
		rewind(stdin);
	}
	*pointer = (Smartphone*)malloc((*count) * sizeof(Smartphone));
	for (int i = 0; i < *count; i++) {
		printf("Initializing %d structer in array\n\n", i + 1);
		initStruct(*pointer + i);
		printf("\nSuccess");
		//Sleep(3000);
		system("cls");
		rewind(stdin);
	}
}

void addToStruct(Smartphone** pointer, int* count) {
	Smartphone* temp = NULL;
	(*count)++;
	temp = (Smartphone*)malloc(sizeof(Smartphone));
	initStruct(temp);
	if ((*pointer) == NULL) {
		(*pointer) = (Smartphone*)malloc((*count) * sizeof(Smartphone));
		(*pointer)[(*count) - 1] = *temp;
	}
	else {
		(*pointer) = (Smartphone*)realloc((*pointer), (*count) * sizeof(Smartphone));
		(*pointer)[(*count) - 1] = *temp;
	}
}

void printStructArray(Smartphone* array, int count) {
	for (int i = 0; i < count; ) {
		printf("-----------------------------Structure number %d-----------------------------\n", i + 1);
		printf("Name: %s\n", array[i].name);
		printf("Screen size: %.2f\n", array[i].screenSize);
		printf("RAM (GB): %d\n", array[i].ram);
		printf("Memory (GB): %d\n", array[i].memory);
		printf("Battery capacity: %d\n", array[i].battery);
		printf("-----------------------------------------------------------------------------\n\n\n");
		i++;
		
	}
}

void deleteStruct(Smartphone** array, int* count) {
	int index;
	int i;
	printf("Enter number of stucture you want to delete: ");
	while ((scanf_s(" %d", &index)) != 1 || getchar() != '\n' || (index < 1 || index > *count)) {
		printf("Invalid input. Enter existing number of struct: ");
		rewind(stdin);
	}
	i = index - 1;
	if ((*array)[i].name != NULL) {
		free((*array)[i].name);
		(*array)[i].name = NULL;
	}
	//free((*array)[i].name);
	(*count)--;
	for (i = index - 1; i < (*count); i++) {
		(*array)[i] = (*array)[i + 1];
	}
	if (*count == 0) {
		free((*array));
		(*array) = NULL;
	}
	else {
		(*array) = (Smartphone*)realloc(*array, (*count) * sizeof(Smartphone));
	}

}