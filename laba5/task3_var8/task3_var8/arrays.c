#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#define TRUE 0
#define FALSE 1

void array_size(int* amountofrows, int* amountofcols)
{
	int input;
	printf("Enter amount of rows N: ");
	while (scanf_s(" %d", &input) == 0 || getchar() != '\n' || input < 1)
	{
		printf("Invalid input. Enter correct amount of rows N: ");
		rewind(stdin);
	}
	*amountofrows = input;
	printf("Enter amount of columns M: ");
	while (scanf_s(" %d", &input) == 0 || getchar() != '\n' || input < 1)
	{
		printf("Invalid input. Enter correct amount of cols M: ");
		rewind(stdin);
	}
	*amountofcols = input;
}
void array_input(int*** array, int amountofrows, int amountofcols)
{
	int input;
	(*array) = (int**)malloc(amountofrows * amountofcols * sizeof(int*));
	for (int i = 0; i < amountofrows; i++)
	{
		(*array)[i] = (int*)malloc(amountofcols * sizeof(int));
		for (int j = 0; j < amountofcols; j++)
		{
			printf("Enter element[%d][%d]: ", i, j);
			while (scanf_s(" %d", &input) == 0 || getchar() != '\n' || amountofcols < 1)
			{
				printf("Invalid input. Enter correct element[%d][%d]: ", i, j);
				rewind(stdin);
			}
			(*array)[i][j] = input;
		}
	}
}
void array_move(int** array, int j, int amountofrows)
{
	for (int i = 0; i < amountofrows; i++)
	{
		*(*(array + i) + j) = *(*(array + i) + j + 1);
	}
}
void array_show(int** array, int amountofrows, int amountofcols)
{
	for (int i = 0; i < amountofrows; i++)
	{
		for (int j = 0; j < amountofcols; j++)
		{
			printf("%d\t", *(*(array + i) + j));
		}
		printf("\n");
	}
}
int array_check_negative_col(int** array, int amountofrows, int j)
{
	int counter = 0;
	for (int i = 0; i < amountofrows; i++)
	{
		if (*(*(array + i) + j) < 0)
		{
			counter++;
		}
	}
	if (counter == amountofrows)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void array_delete(int*** array, int* amountofcols, int* amountofrows)
{
	int amount = *amountofcols;
	for (int j = 0; j < amount; j++)
	{
		if (array_check_negative_col(*array, *amountofrows, j) == TRUE)
		{
			for (int i = 0; i < (*amountofrows); i++)
			{
				for (int k = j; k + 1 < (*amountofcols); k++)
				{
					(*array)[i][k] = (*array)[i][k + 1];
				}
			}
			(*amountofcols)--;
			for (int i = 0; i < (*amountofcols); i++)
			{
				(*array)[i] = (int**)realloc((*array)[i], (*amountofcols) * sizeof(int*));
			}
		}
	}
}
void array_free(int** array, int amountofrows)
{
	for (int i = 0; i < amountofrows; i++)
	{
		free(array[i]);
	}
	free(array);
}