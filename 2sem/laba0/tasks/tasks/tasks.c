#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "myString.h"
#include "input.h"
#include "output.h"
#include "tasks.h"

int task1(void) {
	char* input;
	int compare;
	char ch;
	FILE* in;
	FILE* out;
	printf("In this task you'll be writing numbers into console and programm put them into txt file.\nWrite 'stop' to finish programm.\n");
	fopen_s(&in, "D:/labTests/laba1/task1.txt", "w+");
	Sleep(2000);
	if (in == NULL) {
		printf("Oops... Something went wrong. It's not possible to open the file.");
		exit(1);
	}
	do {
		printf("Enter number: ");
		input = malloc(255 * sizeof(char));
		fgets(input, 255, stdin);
		compare = strcmp(input, "stop\n");
		if (isDigit(input) == 0 && compare != 0) {
			printf("Incorrect input. ");
			free(input);
			continue;
		}
		if (compare != 0) {
			fputs(input, in);
		}
	} while (compare != 0);
	printf("stop is stop : )");
	Sleep(2000);
	system("cls");
	printf("And finally, output:\n");
	fclose(in);
	printFile("D:/labTests/laba1/task1.txt");
	free(input);
}

int task2(void) {
	FILE* fileWithNums;
	int counter = 0;
	int max;
	int tempInt;
	char ch;
	char* tempChar;
	int flag = 0;
	printf("This programm finds max number from txt file and outputs every one of it.");
	//Sleep(5000);
	system("cls");
	fopen_s(&fileWithNums, "D:/labTests/laba1/task2.txt", "r");
	if (fileWithNums == NULL) {
		printf("Oops... Something went wrong. The file doesn't exist.");
		exit(1);
	}
	tempChar = (char*)malloc(255 * sizeof(char));
	while (fgets(tempChar, 255, fileWithNums)) {
		if (isDigit(tempChar) == 0) {
			continue;
		}
		tempInt = atoi(tempChar);
		if (flag == 0) {
			max = tempInt;
			counter++;
			flag = 1;
			continue;
		}
		if (tempInt > max) {
			counter = 1;
			max = tempInt;
		}
		else if (tempInt == max)
			counter++;
	}
	if (counter == 0) {
		printf("File is empty. Fill it with the nums.");
		exit(1);
	}
		
	for (int i = 0; i < counter; i++) {
		printf("%d\n", max);
	}
	free(tempChar);
}

int task3(void) {
	FILE* fileWithNums;
	int userNum;
	int len;
	char* txtNum;
	txtNum = (char*)malloc(255 * sizeof(char));
	fopen_s(&fileWithNums, "D:/labTests/laba1/task3.txt", "r+");
	if (fileWithNums == NULL) {
		printf("Oops... Something went wrong. The file doesn't exist.");
		exit(1);
	}
	printf("Please, enter number of int you want to reverse: ");
	while ((scanf_s("%d", &userNum)) == 0 || getchar() != '\n') {
		printf("Incorrect input. Enter correct number: ");
		rewind(stdin);
	}
	for (int i = 0; i < userNum; i++) {
		fgets(txtNum, 255, fileWithNums);
	}
	len = strlen(txtNum);
	for (int i = 0; i < len / 2; i++) {
		char temp;
		temp = txtNum[i];
		txtNum[i] = txtNum[len - 1 - i];
		txtNum[len - 1 - i] = temp;
	}
	fputs(txtNum, fileWithNums);
}