#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

#define TRUE 1
#define FALSE 0

void arrayInputKeyboard(int*** array, int amountOfRows, int amountOfCols)
{
	*array = (int**)calloc(amountOfRows, sizeof(int*));
	for (int i = 0; i < amountOfRows; i++)
	{
		(*array)[i] = (int*)calloc(amountOfCols, sizeof(int));
	}
	int input;
	for (int i = 0; i < amountOfRows; i++)
	{
		for (int j = 0; j < amountOfCols; j++)
		{
			printf("Enter element [%d][%d]: ", i, j);
			while (scanf_s("%d", &input) == 0 || getchar() != '\n')
			{
				printf("Invalid input. Enter correct element [%d][%d]: ", i, j);
				rewind(stdin);
			}
			(*array)[i][j] = input;
		}
		printf("\n");
	}
}
void arraySize(int* amountofrows, int* amountofcols)
{
	printf("Enter amount of rows N: ");
	while (scanf_s(" %d", amountofrows) == 0 || getchar() != '\n' || *amountofrows < 1)
	{
		printf("Invalid input. Enter correct amount of rows N: ");
		rewind(stdin);
	}
	printf("Enter amount of columns M: ");
	while (scanf_s(" %d", amountofcols) == 0 || getchar() != '\n' || *amountofcols < 1)
	{
		printf("Invalid input. Enter correct amount of rows N: ");
		rewind(stdin);
	}
}
void arrayOutput(int*** array, int amountOfRows, int amountOfCols)
{
	for (int i = 0; i < amountOfRows; i++)
	{
		for (int j = 0; j < amountOfCols; j++)
		{
			printf("%d\t", (*array)[i][j]);
		}
		printf("\n");
	}
}
int arrayMaxCol(int*** array, int amountOfRows, int index)
{
	int max = (*array)[0][index];
	for (int i = 0; i < amountOfRows; i++)
	{
		if (max < (*array)[i][index])
		{
			max = (*array)[i][index];
		}
	}
	return max;
}
void arrayColSwap(int*** array, int amountofrows, int colNum1, int colNum2)
{
	for (int i = 0; i < amountofrows; i++)
	{
		int tempNum = (*array)[i][colNum1];
		(*array)[i][colNum1] = (*array)[i][colNum2];
		(*array)[i][colNum2] = tempNum;
	}
}
void arrayFree(int*** array, int amountOfRows)
{
	for (int i = 0; i < amountOfRows; i++)
	{
		free((*array)[i]);
	}
	free(*array);
}