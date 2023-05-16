#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "menu.h"
#include "structeres.h"
#include "sort.h"
#include "parser.h"

void menuInformation(void) {
	printf("---------------------MENU---------------------\n");
	printf("1) Create array for structure and initialize it\n");
	printf("2) Print array\n");
	printf("3) Sort array with one field\n");
	printf("4) Delete struct from array\n");
	printf("5) Add one struct to array\n");
	printf("6) Sort array with two fields at one time\n");
	printf("7) Parse 21vek.by\n");
	printf("8) Exit\n");
	printf("Your choice: ");
}

void menu1(Smartphone** pointer, int* sizeOfArray) {
	printf("Creating array and initializing it!");
	//Sleep(3000);
	system("cls");
	createStructArr(pointer, sizeOfArray);
}

void menu2(Smartphone** pointer, const int* sizeOfArray) {
	printf("Printing...");
	//Sleep(2000);
	system("cls");
	if ((*pointer) == NULL) {
		printf("Nothing to print - array is empty : (");
		//Sleep(2000);
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
		printf("Nothing to sort - array is empty : (");
		//Sleep(2000);
		system("cls");
	}
	else {
		system("cls");
		printf("What do you want to sort?\n");
		printf("1) Name\n");
		printf("2) Screen size\n");
		printf("3) RAM\n");
		printf("4) Memory\n");
		printf("5) Battery capacity\n");
		printf("6) Exit\n");
		printf("Your choice: ");
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 7)) {
			printf("Invalid input. Enter correct number: ");
		}
		switch (userInput) {
		case 1:
			qsort(*pointer, (*sizeOfArray), sizeof(Smartphone), compareName);
			break;
		case 2:
			qsort(*pointer, (*sizeOfArray), sizeof(Smartphone), compareDiag);
			break;
		case 3:
			qsort(*pointer, (*sizeOfArray), sizeof(Smartphone), compareRam);
			break;
		case 4:
			qsort(*pointer, (*sizeOfArray), sizeof(Smartphone), compareMemory);
			break;
		case 5:
			qsort(*pointer, (*sizeOfArray), sizeof(Smartphone), compareBattery);
			break;
		case 6:
			break;
		default:
			break;
		}
		printf("Success!");
		//Sleep(2000);
		system("cls");
	}

}

void menu4(Smartphone** pointer, int* sizeOfArray) {
	printf("Deleting structure from the array!\n");
	//Sleep(2000);
	if ((*pointer) == NULL) {
		system("cls");
		printf("Nothing to delete - array is empty : (");
		//Sleep(2000);
		system("cls");
	}
	else {
		//Sleep(3000);
		deleteStruct(pointer, sizeOfArray);
		system("cls");
		printf("Success!");
		//Sleep(1000);
	}

}

void menu5(Smartphone** pointer, int* sizeOfArray) {
	addToStruct(pointer, sizeOfArray);
	printf("\nSuccess!");
	//Sleep(2000);
	system("cls");
}

void menu6(Smartphone** pointer, const int* sizeOfArray) {
	qsort(*pointer, (*sizeOfArray), sizeof(Smartphone), compareTwoDiff);
	printf("\nSuccess!");
	//Sleep(2000);
	system("cls");
}

void menu7(Smartphone** pointer, int* sizeOfArray, FILE* filePointer) {
	printf("Parsing...\n\n");
	//Sleep(3000);
	parse(pointer, filePointer, sizeOfArray);
	printf("Success!");
	//Sleep(2000);
	system("cls");
}

void mainMenu(Smartphone** pointer, int* sizeOfArray, FILE* filePointer) {
	int userInput;
	int flag = 0;
	while (1) {
		menuInformation();
		void (*function[7])(Smartphone**, int*, FILE*) = { &menu1, &menu2, &menu3, &menu4, &menu5, &menu6, &menu7 };
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 1 || userInput > 8)) {
			printf("This task doesn't exist. Enter correct number: ");
			rewind(stdin);
		}
		if (userInput == 7) {
			if (flag == 1) {
				printf("You've already parsed 21vek.by");
				//Sleep(2000);
				system("cls");
				continue;
			}
			flag = 1;
		} 
		if (userInput == 8) {
			exit(0);
		}
		function[userInput - 1](pointer, sizeOfArray, filePointer);
	}
}
