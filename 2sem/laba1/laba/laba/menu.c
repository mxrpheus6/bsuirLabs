#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "menu.h"
#include "structeres.h"
#include "sort.h"

void menuInformation() {
	printf("     ����     \n");
	printf("1) ������� ������ �������� � ���������������� ��\n");
	printf("2) ������� ������ �� �����.\n");
	printf("3) ������������� ������ �� ������ ���� ���������\n");
	printf("4) ������� ��������� �� �������\n");
	printf("5) �������� ���� ��������� � ������\n");
	printf("6) ������������� ������ �� ���� ����� ������������ (�� ������, �� ����� ��� ���������� ������ � ������� ��� ������� �������\n");
	printf("7) ����� �� ���������\n");
	printf("��� �����: ");
}

void menu1(Smartphone** pointer, int* sizeOfArray) {
	printf("�������� ������ �������� � �������������� ���!");
	Sleep(3000);
	system("cls");
	createStructArr(pointer, sizeOfArray);
}

void menu2(Smartphone** pointer, const int* sizeOfArray) {
	printf("�������...");
	Sleep(2000);
	system("cls");
	if ((*pointer) == NULL) {
		printf("�������� ������ - ������ ���� : (");
		Sleep(2000);
		system("cls");
	}
	else {
		system("cls");
		printStructArray(*pointer, *sizeOfArray);
	}
}

void menu3(Smartphone** pointer, const int* sizeOfArray) {
	int userInput;
	if ((*pointer) == NULL) {
		system("cls");
		printf("����������� ������ - ������ ���� : (");
		Sleep(2000);
		system("cls");
	}
	else {
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
		default:
			break;
		}
		printf("�����!");
		Sleep(2000);
		system("cls");
	}

}

void menu4(Smartphone** pointer, int* sizeOfArray) {
	printf("������ ��������� �� �������!\n");
	Sleep(2000);
	if ((*pointer) == NULL) {
		system("cls");
		printf("������� ������ - ������ ���� : (");
		Sleep(2000);
		system("cls");
	}
	else {
		Sleep(3000);
		deleteStruct(pointer, sizeOfArray);
		system("cls");
		printf("�����!");
		Sleep(1000);
	}

}

void menu5(Smartphone** pointer, int* sizeOfArray) {
	addToStruct(pointer, sizeOfArray);
	printf("\n�����!");
	Sleep(2000);
	system("cls");
}

void menu6(Smartphone** pointer, int* sizeOfArray) {
	//insertionSort(pointer, *sizeOfArray, sizeof(Smartphone), compareTwoDiff);
	qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareTwoDiff);
	printf("\n�����!");
	Sleep(2000);
	system("cls");
}

void mainMenu(Smartphone** pointer, int* sizeOfArray) {
	int userInput;
	while (1) {
		menuInformation();
		void (*function[6])(Smartphone**, int*) = { &menu1, &menu2, &menu3, &menu4, &menu5, &menu6 };
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 8)) {
			printf("������ ������� �� ����������. ������� ���������� �����: ");
			rewind(stdin);
		}
		if (userInput == 7) {
				exit(0);
		}
		function[userInput - 1](pointer, sizeOfArray);
	
	}
}
