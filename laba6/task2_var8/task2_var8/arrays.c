#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arrays.h"
#define TRUE 1
#define FALSE 0

void array_input_keyboard(int* array1, int s)
{
	int input;
	for (int i = 0; i < s; i++)
	{
		printf("Enter element %d: ", i + 1);
		while (scanf_s("%d", &input) == 0 || getchar() != '\n')
		{
			printf("Invalid input. Enter correct element %d: ", i + 1);
			rewind(stdin);
		}
		array1[i] = input;
	}
}
void array_size(int* amountofrows, int* amountofcols)
{
	printf("Enter amount of rows N: ");
	while (scanf_s(" %d", amountofrows) == 0 || getchar() != '\n' || amountofrows < 1)
	{
		printf("Invalid input. Enter correct amount of rows N: ");
		rewind(stdin);
	}
	while (scanf_s(" %d", amountofcols) == 0 || getchar() != '\n' || amountofcols < 1)
	{
		printf("Invalid input. Enter correct amount of rows N: ");
		rewind(stdin);
	}
}
void array_start_memory(int** array1, int sizeofarray)
{
	*array1 = (int*)malloc(sizeofarray * sizeof(int));
}
void array_output(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", (*array)[i]);
	}
}
void array_free(int** array, int amountofrows)
{
	free(*array);
}