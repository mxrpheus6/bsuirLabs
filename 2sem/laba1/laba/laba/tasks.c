#include <stdio.h>
#include <Windows.h>

#include "tasks.h"
#include "structeres.h"
#include "sort.h"

void task1(Smartphone* pointer, int* sizeOfArray) {
	printf("�������� ������ ��������!");
	//Sleep(5000);
	system("cls");
	createStructArr(&pointer, &sizeOfArray);
	printStructArray(pointer, sizeOfArray);
	printf("��� �� ������ �������������?");
//	qsort(pointer, (int)sizeOfArray, sizeof(Smartphone), compareBattery);
	printStructArray(pointer, sizeOfArray);
}