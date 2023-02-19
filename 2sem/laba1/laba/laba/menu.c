#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "menu.h"
#include "structeres.h"
#include "tasks.h"
#include "sort.h"

void menuInformation() {
	printf("     ����     \n");
	printf("1) ������� ������ �������� � ���������������� ��.\n");
	printf("2) ������� ������ �� �����.\n");
	printf("3) ������������� ������ �� ������ ���� ���������.\n");
	//printf("4) ������������� ������ �� ���� ����� ������������.\n");
	//printf("5) ������� ��������� �� �������.\n");
	printf("4) ����� �� ���������.\n");
	printf("��� �����: ");
}

void menu1(Smartphone** pointer, int* sizeOfArray) {
	printf("�������� ������ �������� � �������������� ���!");
	//Sleep(5000);
	system("cls");
	createStructArr(pointer, sizeOfArray);
}

void menu2(Smartphone** pointer, int* sizeOfArray) {
	printf("�������...");
	//Sleep(2000);
	system("cls");
	printStructArray(*pointer, *sizeOfArray);
}

void menu3(Smartphone** pointer, int* sizeOfArray) {
	int userInput;
	system("cls");
	printf("��� �� ������ �������������?\n");
	printf("1) ��������\n");
	printf("2) ��������� ������\n");
	printf("3) ����������� ������\n");
	printf("4) ���������� ������\n");
	printf("5) ���������� ������\n");
	printf("6) ������� �������\n");
	printf("7) �����\n");
	printf("��� �����: ");
	while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 7)) {
		printf("������������ ����. ������� ���������� �����: ");
	}
	switch (userInput) {
	case 1:
		qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareName);
		break;
	case 2:
		qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareDiag);
		break;
	case 3:
		qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareRam);
		break;
	case 4:
		qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareMemory);
		break;
	case 5:
		qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareCamera);
		break;
	case 6:
		qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareBattery);
		break;
	case 7:
		break;
	}
	printf("�����!");
	Sleep(2000);
	system("cls");
}

void menu4(Smartphone** pointer, int* sizeOfArray) {
	exit(0);
}

void mainMenu(Smartphone** pointer, int* sizeOfArray) {
	int userInput;
	while (1) {
		menuInformation();
		void (*function[4])(Smartphone**, int*) = { &menu1, &menu2, &menu3, &menu4 };
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 4)) {
			printf("������ ������� �� ����������. ������� ���������� �����: ");
			rewind(stdin);
		}
		function[userInput - 1](pointer, sizeOfArray);
		if (userInput == 4) {
			break;
		}
	}
}
