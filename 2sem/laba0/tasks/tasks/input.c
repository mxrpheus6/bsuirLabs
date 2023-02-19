#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "input.h"

void taskNum(int* num) {
	printf("Hello! I'm glad that my creator survived exams. Here is tasks from Pavel Kazachenko group No.250504\nChoose task (1/2/3): ");
	while (scanf_s("%d", num) == 0 || getchar() != '\n' || ((*num) < 1 || (*num) > 3)) {
		printf("Incorrect! Enter number from the list: ");
		rewind(stdin);
	}
	printf("Great choice!");
	Sleep(3000);
	system("cls");
}

//void stringWithoutSize(char** str) {
//	char sym;
//	int len = 1;
//	*str = (char*)malloc(sizeof(char));
//	while ((sym = getchar()) != '\n') {
//		(*str)[len - 1] = sym;
//		len++;
//		(*str) = (char*)realloc(*str, len);
//	}
//	(*str)[len - 1] = '\0';
//}