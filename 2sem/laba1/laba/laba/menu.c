#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "menu.h"
#include "structeres.h"
#include "sort.h"

void menuInformation() {
	printf("     МЕНЮ     \n");
	printf("1) Создать массив структур и инициализировать их\n");
	printf("2) Вывести массив на экран.\n");
	printf("3) Отсортировать массив по одному полю структуры\n");
	printf("4) Удалить структуру из массива\n");
	printf("5) Добавить одну структуру в массив\n");
	printf("6) Отсортировать массив по двум полям одновременно (по камере, но чтобы все одинаковая камера в порядке шли емкости батареи\n");
	printf("7) Выход из программы\n");
	printf("Ваш выбор: ");
}

void menu1(Smartphone** pointer, int* sizeOfArray) {
	printf("Создадим массив структур и инициализируем его!");
	Sleep(3000);
	system("cls");
	createStructArr(pointer, sizeOfArray);
}

void menu2(Smartphone** pointer, const int* sizeOfArray) {
	printf("Выводим...");
	Sleep(2000);
	system("cls");
	if ((*pointer) == NULL) {
		printf("Выводить нечего - массив пуст : (");
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
		printf("Сортировать нечего - массив пуст : (");
		Sleep(2000);
		system("cls");
	}
	else {
		system("cls");
		printf("Что вы хотите отсортировать?\n");
		printf("1) Название\n");
		printf("2) Диагональ экрана\n");
		printf("3) Оперативная память\n");
		printf("4) Постоянная память\n");
		printf("5) Разрешение камеры\n");
		printf("6) Емкость батареи\n");
		printf("7) Выход\n");
		printf("Ваш выбор: ");
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 7)) {
			printf("Некорректный ввод. Введите правильный номер: ");
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
		printf("Успех!");
		Sleep(2000);
		system("cls");
	}

}

void menu4(Smartphone** pointer, int* sizeOfArray) {
	printf("Удалим структуру из массива!\n");
	Sleep(2000);
	if ((*pointer) == NULL) {
		system("cls");
		printf("Удалять нечего - массив пуст : (");
		Sleep(2000);
		system("cls");
	}
	else {
		Sleep(3000);
		deleteStruct(pointer, sizeOfArray);
		system("cls");
		printf("Успех!");
		Sleep(1000);
	}

}

void menu5(Smartphone** pointer, int* sizeOfArray) {
	addToStruct(pointer, sizeOfArray);
	printf("\nУспех!");
	Sleep(2000);
	system("cls");
}

void menu6(Smartphone** pointer, int* sizeOfArray) {
	//insertionSort(pointer, *sizeOfArray, sizeof(Smartphone), compareTwoDiff);
	qsort(*pointer, (int)(*sizeOfArray), sizeof(Smartphone), compareTwoDiff);
	printf("\nУспех!");
	Sleep(2000);
	system("cls");
}

void mainMenu(Smartphone** pointer, int* sizeOfArray) {
	int userInput;
	while (1) {
		menuInformation();
		void (*function[6])(Smartphone**, int*) = { &menu1, &menu2, &menu3, &menu4, &menu5, &menu6 };
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 8)) {
			printf("Такого задания не существует. Введите корректный номер: ");
			rewind(stdin);
		}
		if (userInput == 7) {
				exit(0);
		}
		function[userInput - 1](pointer, sizeOfArray);
	
	}
}
