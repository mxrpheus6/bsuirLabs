#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "files.h"

#include "bmpReader.h"

void menuInformation(void) {
	printf("---------------------MENU---------------------\n");
	printf("1) Create BW image\n");
	printf("2) Create negative image\n");
	printf("3) Make gamma correction\n");
	printf("4) Change original photo\n");
	printf("5) Test\n");
	printf("Your choice: ");
}

void mainMenu(char* path, FILE** newFile, float* gamma) {
	BMPFile* bmpf;
	int flag = 0;
	printf("Welcome!\nPlease, enter name of original bmp file: ");
	fgets(path, 256, stdin);
	path[strlen(path) - 1] = '\0';
	int userInput;
	while ((bmpf = loadBMPFile(path)) == 1) {
		fgets(path, 256, stdin);
		path[strlen(path) - 1] = '\0';
	}
	system("cls");
	while (1) {
		menuInformation();
		flag = 0;
		while ((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n' || (userInput < 0 || userInput > 5)) {
			if (flag == 1) {
				break;
			}
			if (userInput == 4) {
				exit(0);
			}
			flag = 1;
		}
		switch (userInput) {
		case 1:
			createNewFile(path);
			createBWImage(bmpf, newFile, path);
			printf("\nSuccess!");
			Sleep(1000);
			system("cls");
			break;
		case 2:
			createNewFile(path);
			createNegativeImage(bmpf, newFile, path);
			printf("\nSuccess!");
			Sleep(1000);
			system("cls");
			break;
		case 3:
			createNewFile(path);
			system("cls");
			printf("Please, enter gamma correction value: ");
			while ((scanf_s(" %f", gamma)) != 1 || getchar() != '\n') {
				printf("Invalid input. Please, enter correct value: ");
				rewind(stdin);
			}
			GammaCorrection(bmpf, newFile, *gamma, path);
			printf("\nSuccess!");
			Sleep(1000);
			system("cls");
			break;
		case 4:
			printf("Please, enter name of original bmp file: ");
			fgets(path, 256, stdin);
			path[strlen(path) - 1] = '\0';
			while ((bmpf = loadBMPFile(path)) == 1) {
				fgets(path, 256, stdin);
				path[strlen(path) - 1] = '\0';
			}
			printf("\nSuccess!");
			Sleep(1000);
			system("cls");
			break;
		case 5:
			medianFilter(bmpf, newFile, "obj\\test.bmp", 5);
		default:
			break;
		}
	}
	freeBMPFile(bmpf);
}