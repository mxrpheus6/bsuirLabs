#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

void array_size(int* amountofrows)
{
	int input;
	printf("Enter amount of rows: ");
	while (scanf_s(" %d", &input) == 0 || getchar() != '\n' || input < 1)
	{
		printf("Invalid input. Enter correct amount of rows: ");
		rewind(stdin);
	}
	(*amountofrows) = input;
}
void array_output(int*** array, int rows, int cols)
{
	printf("\n");
	for (int i = 0; i < rows; i++)
	{
		cols = 1;
		for (int j = 0; j < cols; j++)
		{
			if ((*array)[i][j] != -1)
			{
				printf("%d\t", (*array)[i][j]);
				cols++;
			}
		}
		printf("%d\n", -1);
	}
}
int array_cols_amount(int* array, int size)
{
	int total = 1;
	for (int i = 0; i < total; i++)
	{
		if (array[i] != -1)
		{
			total++;
		}
	}
	return total;
}
void array_start_memory(int*** array, int sizeofarray)
{
	*array = (int**)malloc(sizeofarray * sizeof(int*));
}
void array_input(int*** array, int* amountofrows, int* amountofcols)
{
	int input;
	for (int i = 0; i < (*amountofrows); i++)
	{
		*amountofcols = 1;
		(*array)[i] = (int*)malloc((*amountofcols) * sizeof(int));
		for (int j = 0; j < (*amountofcols); j++)
		{
			printf("Enter element[%d][%d]: ", i, j);
			while (scanf_s(" %d", &input) == 0 || getchar() != '\n')
			{
				printf("Invalid input. Enter correct element[%d][%d]: ", i, j);
				rewind(stdin);
			}
			(*array)[i][j] = input;
			if (input != -1)
			{
				(*amountofcols)++;
				(*array)[i] = (int**)realloc((*array)[i], (*amountofcols) * sizeof(int*));
			}
			else
			{
				break;
			}

		}
	}
}
void array_move(int*** array, int amountofrows, int* amountofcols)
{
	int counter;
	int checker;
	for (int i = 0; i < amountofrows; i++)
	{
		counter = 1;
		(*amountofcols) = array_cols_amount((*array)[i], &amountofcols);
		for (int j = 0; j < (*amountofcols); j++)
		{
			checker = 0;
			if ((*array)[i][j] != -1)
			{
				if ((*array)[i][j] % 2 == 0 && counter % 2 == 0)
				{
					for (; (*array)[i][j] != -1; j++)
					{
						(*array)[i][j] = (*array)[i][j + 1];
						checker++;
					}
					j -= checker;
					(*array)[i] = (int*)realloc((*array)[i], ((*amountofcols) - 1) * sizeof(int));
					counter = 0;
					(*amountofcols)--;
				}
				else
				{
					counter++;
				}
			}
		}
	}
}
void array_free(int** array, int amountofrows)
{
	for (int i = 0; i < amountofrows; i++)
	{
		free(*(array + i));
	}
	free(array);
}