#include <stdio.h>
#include "intput.h"

void taskNum(int* num) {
	printf("Hello. This programm includes two tasks from LAB 7. What task do you want to chose? (1/2): ");
	while ((scanf_s("%d", num) == 0) || getchar() != '\n') {
		printf("Invaild input. Enter correct task: ");
		rewind(stdin);
	}
}