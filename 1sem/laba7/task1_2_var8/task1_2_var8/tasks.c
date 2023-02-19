#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "tasks.h"

void task1() {
	char* string = (char*)malloc(256);
	int k;
	printf("\nTask 1\n\nThis programm removes words in string with length less than k. Please, enter k: ");
	while ((scanf_s("%d", &k) != 1 || getchar() != '\n')) {
		printf("Invalid input. Please, enter correct k: ");
		rewind(stdin);
	}
	printf("Success! Now enter your string of words: ");
	getString(&string);
	stringRemoveTrailingSpaces(&string);
	stringRemoveWord(&string, k);
	printf("%s", string);
	if (stringLength(string) > 1) {
		free(string);
	}
}

void task2() {
	char* S = (char*)malloc(256);
	char* S0 = (char*)malloc(256);
	printf("\nTask 2\n\nThis programm removes first substring matching S0 from S. If there is no matching strings then output S without changes. Please, enter S: ");
	getString(&S);
	printf("Success! Now enter S0: ");
	getString(&S0);
	findDeleteSubstring(&S, &S0);
	printf("%s", S);
	if (stringLength(S) > 1) {
		free(S);
	}
	if (stringLength(S0) > 1) {
		free(S0);
	}
}