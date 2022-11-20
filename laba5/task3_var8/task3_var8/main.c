#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#define TRUE 0
#define FALSE 1

int main(void)
{
	int amountofrows, amountofcols;
	int** numbers;
	int number;
	printf("LAB 5 TASK 3 by Kazachenko Pavel from GROUP 250504\n\n");
	array_size(&amountofrows, &amountofcols);
	array_input(&numbers, amountofrows, amountofcols);
	printf("\nArray before changes:\n\n");
	array_show(numbers, amountofrows, amountofcols);
	array_delete(&numbers, &amountofcols, &amountofrows);
	printf("\nArray after changes:\n\n");
	array_show(numbers, amountofrows, amountofcols);
	array_free(numbers, amountofrows);
	return 0;
}