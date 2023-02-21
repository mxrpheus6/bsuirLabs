#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "structeres.h"
#include "memory.h"

void initStruct(Smartphone* pointer) {
	int userInput;
	RamTypes capacity;
	printf("Введите название: ");
	charMemoryAllocate(&pointer->name);
	fgets(pointer->name, 255, stdin);
	charMemoryRelocate(&pointer->name);
	printf("Введите диагональ экрана: ");
	while ((scanf_s(" %f", &pointer->screenSize)) != 1 || getchar() != '\n' || pointer->screenSize <= 0) {
		printf("Ошибка ввода. Введите корректную диагональ: ");
		rewind(stdin);
	}
	printf("Введите оперативную память (GB): ");
	while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput != 2 && userInput != 4 && userInput != 6 && userInput != 8)) {
		printf("Ошибка ввода. Введите корректную память: ");
		rewind(stdin);
	}
	capacity = (RamTypes)userInput;
	pointer->ram = capacity;
	printf("Введите постоянную память (GB): ");
	while ((scanf_s(" %d", &pointer->memory)) != 1 || getchar() != '\n' || pointer->memory <= 0) {
		printf("Ошибка ввода. Введите корректную память: ");
		rewind(stdin);
	}
	rewind(stdin);
	printf("Введите разрешение камеры (mp): ");
	while ((scanf_s(" %d", &pointer->cameraResolution)) != 1 || getchar() != '\n' || pointer->cameraResolution <= 0) {
		printf("Ошибка ввода. Введите корректное разрешение: ");
		rewind(stdin);
	}
	printf("Введите емкость батареи (mAh): ");
	while ((scanf_s(" %d", &pointer->battery)) != 1 || getchar() != '\n' || pointer->battery <= 0) {
		printf("Ошибка ввода. Введите корректную емкость батареи: ");
		rewind(stdin);
	}
	rewind(stdin);
}

void createStructArr(Smartphone** pointer, int* count) {
	printf("Введите размер массива структур: ");
	while ((scanf_s(" %d", count)) != 1 || getchar() != '\n' || *count <= 0) {
		printf("Ошибка ввода. Введите корректный размер: ");
		rewind(stdin);
	}
	*pointer = (Smartphone*)malloc((*count) * sizeof(Smartphone));
	for (int i = 0; i < *count; i++) {
		printf("Инициализируем %d структуру в массиве\n\n", i + 1);
		initStruct(*pointer + i);
		printf("\nУспех!");
		Sleep(3000);
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
		printf("Структура номер %d\n\n", i + 1);
		printf("Название: %s\n", array[i].name);
		printf("Диагональ экрана: %.1f\n", array[i].screenSize);
		printf("Оперативная память (Gb): %d\n", array[i].ram);
		printf("Постоянная память (Gb): %d\n", array[i].memory);
		printf("Разрешение камеры: %d\n", array[i].cameraResolution);
		printf("Емкость батареи: %d\n", array[i].battery);
		printf("\nНажмите клавишу 'Enter' чтобы перейти к следующей структуре.");
		if (getchar() != 0) {
			system("cls");
			i++;
		}
	}
}

void deleteStruct(Smartphone** array, int* count) {
	int index;
	int i;
	printf("Введите номер структуры, которую вы хотите удалить: ");
	while ((scanf_s(" %d", &index)) != 1 || getchar() != '\n' || (index < 1 || index > count)) {
		printf("Некорректный ввод. Введите номер существующей стркутры для удаления: ");
		rewind(stdin);
	}
	i = index - 1;
	free((*array)[i].name);
	for (; i < (*count); i++) {
		(*array)[i] = (*array)[i + 1];
	}
	(*count)--;
	(*array) = (Smartphone*)realloc(*array, (*count) * sizeof(Smartphone));
}