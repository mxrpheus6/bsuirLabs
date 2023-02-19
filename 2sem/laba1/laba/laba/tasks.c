#include <stdio.h>
#include <Windows.h>

#include "tasks.h"
#include "structeres.h"
#include "sort.h"

void task1(Smartphone* pointer, int* sizeOfArray) {
	printf("Создадим массив структур!");
	//Sleep(5000);
	system("cls");
	createStructArr(&pointer, &sizeOfArray);
	printStructArray(pointer, sizeOfArray);
	printf("Что вы хотите отсортировать?");
//	qsort(pointer, (int)sizeOfArray, sizeof(Smartphone), compareBattery);
	printStructArray(pointer, sizeOfArray);
}