#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "structeres.h"
#include "memory.h"

void initStruct(Smartphone* pointer) {
	int userInput;
	RamTypes capacity;
	printf("������� ��������: ");
	charMemoryAllocate(&pointer->name);
	fgets(pointer->name, 255, stdin);
	charMemoryRelocate(&pointer->name);
	printf("������� ��������� ������: ");
	scanf_s(" %f", &pointer->screenSize);
	printf("������� ����������� ������ (GB): ");
	scanf_s(" %d", &userInput);
	capacity = (RamTypes)userInput;
	printf("������� ���������� ������ (GB): ");
	scanf_s(" %d", &pointer->memory);
	rewind(stdin);
	printf("������� ������ ��: ");
	charMemoryAllocate(&pointer->osVersion);
	fflush(stdin);
	fgets(pointer->osVersion, 255, stdin);
	charMemoryRelocate(&pointer->osVersion);
	printf("������� ���������� ������ (mp): ");
	scanf_s(" %d", &pointer->cameraResolution);
	printf("������� ���������� SIM ����: ");
	scanf_s(" %d", &pointer->simCardAmount);
	printf("������� ������� ������� (mAh): ");
	scanf_s(" %d", &pointer->battery);
}

void createStructArr(Smartphone** pointer, int* count) {
	printf("������� ������ ������� ��������: ");
	while ((scanf_s(" %d", count)) != 1 || getchar() != '\n' || *count <= 0) {
		printf("������ �����. ������� ���������� ������: ");
		rewind(stdin);
	}
	*pointer = (Smartphone*)malloc((*count) * sizeof(Smartphone));
	for (int i = 0; i < *count; i++) {
		printf("�������������� %d ��������� � �������\n\n", i + 1);
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