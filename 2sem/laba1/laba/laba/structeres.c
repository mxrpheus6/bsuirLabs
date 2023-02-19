#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "structeres.h"
#include "memory.h"

void initStruct(Smartphone* pointer) {
	int userInput;
	RamTypes capacity;
	printf("¬ведите название: ");
	charMemoryAllocate(&pointer->name);
	fgets(pointer->name, 255, stdin);
	charMemoryRelocate(&pointer->name);
	printf("¬ведите диагональ экрана: ");
	scanf_s(" %f", &pointer->screenSize);
	printf("¬ведите оперативную пам€ть (GB): ");
	scanf_s(" %d", &userInput);
	capacity = (RamTypes)userInput;
	printf("¬ведите посто€нную пам€ть (GB): ");
	scanf_s(" %d", &pointer->memory);
	rewind(stdin);
	printf("¬ведите версию ќ—: ");
	charMemoryAllocate(&pointer->osVersion);
	fflush(stdin);
	fgets(pointer->osVersion, 255, stdin);
	charMemoryRelocate(&pointer->osVersion);
	printf("¬ведите разрешение камеры (mp): ");
	scanf_s(" %d", &pointer->cameraResolution);
	printf("¬ведите количество SIM карт: ");
	scanf_s(" %d", &pointer->simCardAmount);
	printf("¬ведите емкость батареи (mAh): ");
	scanf_s(" %d", &pointer->battery);
}

void createStructArr(Smartphone** pointer, int* count) {
	printf("¬ведите размер массива структур: ");
	while ((scanf_s(" %d", count)) != 1 || getchar() != '\n' || *count <= 0) {
		printf("ќшибка ввода. ¬ведите корректный размер: ");
		rewind(stdin);
	}
	*pointer = (Smartphone*)malloc((*count) * sizeof(Smartphone));
	for (int i = 0; i < *count; i++) {
		printf("»нициализируем %d структуру в массиве\n\n", i + 1);
		initStruct(*pointer + i);
		printf("\nSuccess!");
		Sleep(3000);
		system("cls");
		rewind(stdin);
	}
}

void printStructArray(Smartphone* array, int count) {
	for (int i = 0; i < count; i++) {
		printf("%s\n", array[i].name);
	}
}