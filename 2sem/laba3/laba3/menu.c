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
	printf("4) Make median filter\n");
	printf("5) Change original photo\n");
	printf("6) Exit\n");
	printf("Your choice: ");
}

void mainMenu(char* path, FILE** newFile, float* gamma, int* window) {
	BMPFile* bmpf;
	int flag = 0;
	printf("Welcome!\nPlease, enter name of original bmp file: ");
	fgets(path, 256, stdin);
	path[strlen(path) - 1] = '\0';
	int userInput;
	while ((bmpf = loadBMPFile(path)) == 1 || (bmpf = loadBMPFile(path)) == 2) {
		fgets(path, 256, stdin);
		path[strlen(path) - 1] = '\0';
	}
	system("cls");
	while (1) {
		menuInformation();
		while (((scanf_s(" %d", &userInput)) != 1 || getchar() != '\n') || (userInput < 0 || userInput > 6)) {
			printf("Invalid input. Please, enter correct number: ");
			rewind(stdin);
		}
		if (userInput == 6) {
			freeBMPFile(bmpf);
			exit(0);
		}
		switch (userInput) {
		case 1:
			createNewFile(path);
			createBWImage(bmpf, newFile, path);
			printf("\nSuccess!");
			//Sleep(1000);
			system("cls");
			break;
		case 2:
			createNewFile(path);
			createNegativeImage(bmpf, newFile, path);
			printf("\nSuccess!");
			//Sleep(1000);
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
			//Sleep(1000);
			system("cls");
			break;
		case 4:
			createNewFile(path);
			system("cls");
			printf("Please, enter filter window size (it must be odd number!!!): ");
			while ((scanf_s(" %d", window)) != 1 || getchar() != '\n' || (*window) % 2 == 0 || (*window) <= 1) {
				printf("Invalid input. Please, enter correct value: ");
				rewind(stdin);
			}
			medianFilter(bmpf, newFile, path, *window);
			printf("\nSuccess!");
			//Sleep(1000);
			system("cls");
			break;
		case 5:
			printf("Please, enter name of original bmp file: ");
			fgets(path, 256, stdin);
			path[strlen(path) - 1] = '\0';
			while ((bmpf = loadBMPFile(path)) == 1) {
				fgets(path, 256, stdin);
				path[strlen(path) - 1] = '\0';
			}
			printf("\nSuccess!");
			//Sleep(1000);
			system("cls");
			break;
		default:
			break;
		}
	}
}