#include <stdio.h>
#include "intput.h"

void taskNum(int* num) {
	printf("This programm includes two tasks from LAB 7. What task do you want to chose? (1/2): ");
	while (scanf_s("%d", num) == 0 || getchar() != '\n' || ((*num) < 1 || (*num) > 2)) {
		printf("Invaild input. Enter correct task: ");
		rewind(stdin);
	}
}