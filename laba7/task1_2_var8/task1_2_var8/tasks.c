#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "tasks.h"

void task1() {
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
}

void task2() {
	char* S = (char*)calloc(1, 1);
	char* S0 = (char*)calloc(1, 1);
	printf("Task 2\nThis programm removes first substring matching S0 from S. If there is no matching strings then output S without changes. Please, enter S: ");
	getString(&S);
	printf("Success! Now enter S0: ");
	getString(&S0);
	findDeleteSubstring(&S, &S0);
	printf("%s", S);
}
