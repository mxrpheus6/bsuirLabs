#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "tasks.h"

void task1()
{
	char* string = (char*)calloc(1, 1);
	int k;
	printf("Task 1\nThis programm removes words in string with length less than k. Please, enter k: ");
	while ((scanf_s("%d", &k) != 1 || getchar() != '\n')) {
		printf("Invalid input. Please, enter correct k: ");
		rewind(stdin);
	}
	printf("Success! Now enter your string of words: ");
	getString(&string);
	stringRemoveTrailingSpaces(&string);
	stringRemoveWord(&string, k);
	printf("%s", string);
	printf("%d", 1);
}

void task2() {

}
