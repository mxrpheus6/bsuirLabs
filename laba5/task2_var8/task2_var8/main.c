#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#define MAXCH 12

int main(void)
{
	int amountofrows, amountofcols, input, counter;
	int** numbers;
	printf("Enter amount of rows: ");
	while (scanf_s(" %d", &amountofrows) == 0 || getchar() != '\n' || amountofrows < 1)
	{
		printf("Invalid input. Enter correct amount of rows: ");
		rewind(stdin);
	}
	numbers = (int**)malloc(amountofrows * sizeof(int*));
	for (int i = 0; i < amountofrows; i++)
	{
		amountofcols = 1;
		numbers[i] = (int*)malloc(amountofcols * sizeof(int));
		for (int j = 0; j < amountofcols; j++)
		{
			printf("Enter element[%d][%d]: ", i, j);
			while (scanf_s(" %d", &input) == 0 || getchar() != '\n')
			{
				printf("Invalid input. Enter correct element[%d][%d]: ", i, j);
				rewind(stdin);
			}
			numbers[i][j] = input;
			if (input != -1)
			{
				amountofcols++;
				numbers[i] = (int*)realloc(*(numbers + i), amountofcols * sizeof(int));
			}
			else
			{
				break;
			}

		}
	}
	printf("\nArray before changes:\n");
	array_output(numbers, amountofrows, &amountofcols);
	for (int i = 0; i < amountofrows; i++)
	{
		counter = 1;
		array_cols_amount(numbers[i], &amountofcols);
		for (int j = 0; j < amountofcols; j++)
		{
			if (numbers[i][j] != -1)
			{
				if (*(*(numbers + i) + j) % 2 == 0 && counter % 2 == 0)
				{
					array_move(numbers, i, j);
					numbers[i] = (int*)realloc(numbers[i], (amountofcols - 1) * sizeof(int));
					counter = 0;
					amountofcols--;
				}
				else
				{
					counter++;
				}
			}
		}
	}
	printf("\n\nArray after changes:\n");
	array_output(numbers, amountofrows, &amountofcols);
	return 0;
}