#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

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
	while ((scanf_s(" %f", &pointer->screenSize)) != 1 || getchar() != '\n' || pointer->screenSize <= 0) {
		printf("������ �����. ������� ���������� ���������: ");
		rewind(stdin);
	}
	printf("������� ����������� ������ (GB): ");
	while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput != 2 && userInput != 4 && userInput != 6 && userInput != 8)) {
		printf("������ �����. ������� ���������� ������: ");
		rewind(stdin);
	}
	capacity = (RamTypes)userInput;
	pointer->ram = capacity;
	printf("������� ���������� ������ (GB): ");
	while ((scanf_s(" %d", &pointer->memory)) != 1 || getchar() != '\n' || pointer->memory <= 0) {
		printf("������ �����. ������� ���������� ������: ");
		rewind(stdin);
	}
	rewind(stdin);
	printf("������� ���������� ������ (mp): ");
	while ((scanf_s(" %d", &pointer->cameraResolution)) != 1 || getchar() != '\n' || pointer->cameraResolution <= 0) {
		printf("������ �����. ������� ���������� ����������: ");
		rewind(stdin);
	}
	printf("������� ������� ������� (mAh): ");
	while ((scanf_s(" %d", &pointer->battery)) != 1 || getchar() != '\n' || pointer->battery <= 0) {
		printf("������ �����. ������� ���������� ������� �������: ");
		rewind(stdin);
	}
	rewind(stdin);
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
		printf("\n�����!");
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
		printf("��������� ����� %d\n\n", i + 1);
		printf("��������: %s\n", array[i].name);
		printf("��������� ������: %.1f\n", array[i].screenSize);
		printf("����������� ������ (Gb): %d\n", array[i].ram);
		printf("���������� ������ (Gb): %d\n", array[i].memory);
		printf("���������� ������: %d\n", array[i].cameraResolution);
		printf("������� �������: %d\n", array[i].battery);
		printf("\n������� ������� 'Enter' ����� ������� � ��������� ���������.");
		if (getchar() != 0) {
			system("cls");
			i++;
		}
	}
}

void deleteStruct(Smartphone** array, int* count) {
	int index;
	int i;
	printf("������� ����� ���������, ������� �� ������ �������: ");
	while ((scanf_s(" %d", &index)) != 1 || getchar() != '\n' || (index < 1 || index > count)) {
		printf("������������ ����. ������� ����� ������������ �������� ��� ��������: ");
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