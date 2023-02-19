#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

int main(void)
{
	int amountofrows, amountofcols, input, counter;
	int** numbers;
	printf("LAB 5 TASK 2 by Kazachenko Pavel from GROUP 250504\n\n");
	array_size(&amountofrows);
	array_start_memory(&numbers, amountofrows);
	array_input(&numbers, &amountofrows, &amountofcols);
	printf("\nArray before changes:\n");
	array_output(&numbers, amountofrows, amountofcols);
	array_move(&numbers, amountofrows, &amountofcols);
	printf("\n\nArray after changes:\n");
	array_output(&numbers, amountofrows, amountofcols);
	array_free(numbers, amountofrows);
	return 0;
}