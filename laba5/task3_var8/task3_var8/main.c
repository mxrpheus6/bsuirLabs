#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#define MAXCH 12
#define TRUE 0
#define FALSE 1

int main(void)
{
	int amountofrows, amountofcols, input, counter;
	int** numbers;
	printf("LAB 5 TASK 3 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter amount of rows N: ");
	while (scanf_s(" %d", &amountofrows) == 0 || getchar() != '\n' || amountofrows < 1)
	{
		printf("Invalid input. Enter correct amount of rows N: ");
		rewind(stdin);
	}
	printf("Enter amount of columns M: ");
	while (scanf_s(" %d", &amountofcols) == 0 || getchar() != '\n' || amountofcols < 1)
	{
		printf("Invalid input. Enter correct amount of rows M: ");
		rewind(stdin);
	}
	numbers = (int**)malloc(amountofrows * amountofcols * sizeof(int*));
	for (int i = 0; i < amountofrows; i++)
	{
		numbers[i] = (int*)malloc(amountofcols * sizeof(int));
		for (int j = 0; j < amountofcols; j++)
		{
			printf("Enter element[%d][%d]: ", i, j);
			while (scanf_s(" %d", &input) == 0 || getchar() != '\n' || amountofcols < 1)
			{
				printf("Invalid input. Enter correct element[%d][%d]: ", i, j);
				rewind(stdin);
			}
			numbers[i][j] = input;
		}
	}
	printf("\nArray before changes:\n\n");
	array_show(numbers, amountofrows, amountofcols);
	for (int j = 0; j < amountofcols; j++)
	{
		if (array_check_negative_col(numbers, amountofrows, j) == TRUE)
		{
			array_delete(numbers, amountofrows, &amountofcols, j);
			for (int i = 0; i < amountofrows; i++)
			{
				numbers[i] = (int*)realloc(numbers[i], amountofcols * sizeof(int*));
			}
		}
	}
	printf("\nArray after changes:\n\n");
	array_show(numbers, amountofrows, amountofcols);
	for (int i = 0; i < amountofrows; i++)
	{
		free(numbers[i]);
	}
	free(numbers);
	return 0;
}