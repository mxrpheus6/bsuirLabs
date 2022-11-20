#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arrays.h"
#define TRUE 1
#define FALSE 0

void array_input_keyboard(int* array1, int* array2, int size)
{
	int input;
	for (int i = 0; i < size; i++)
	{
		printf("Enter element %d: ", i + 1);
		while (scanf_s("%d", &input) == 0 || getchar() != '\n')
		{
			printf("Invalid input. Enter correct element %d: ", i + 1);
			rewind(stdin);
		}
		array1[i] = input;
		array2[i] = input;
	}
}
void array_input_random(int* array1, int* array2, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (rand() % 2 == 0)
		{
			array1[i] = rand() % 100;
			array2[i] = array1[i];
		}
		else
		{
			array1[i] = -rand() % 100;
			array2[i] = array1[i];
		}
	}
}
void array_choice(char* choice, char* check_k, char* check_r)
{
	int maxch = 12;
	printf("Do you want to fill the array from the keyboard or randomly? (k/r): ");
	fgets(choice, maxch, stdin);
	while (compare_strings(choice, check_k) != TRUE && compare_strings(choice, check_r) != TRUE)
	{
		printf("Invalid input. Enter correct answer (k/r): ");
		fgets(choice, maxch, stdin);
	}
}
void array_size(int* amountofrows)
{
	int input;
	printf("Enter size of array: ");
	while (scanf_s(" %d", &input) == 0 || getchar() != '\n' || input < 1)
	{
		printf("Invalid input. Enter correct size of array: ");
		rewind(stdin);
	}
	(*amountofrows) = input;
}
void array_start_memory(int** array1, int** array2, int sizeofarray)
{
	*array1 = (int*)malloc(sizeofarray * sizeof(int));
	*array2 = (int*)malloc(sizeofarray * sizeof(int));
}
void array_output(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", (*array)[i]);
	}
}
void compare_choice(int** array1, int** array2, char* choice, char* check_k, int sizeofarray)
{
	if (compare_strings(choice, check_k) == TRUE)
	{
		array_input_keyboard(*array1, *array2, sizeofarray);
	}
	else
	{
		srand(time(NULL));
		array_input_random(*array1, *array2, sizeofarray);
	}
}
void array_worst(int** array, int sizeofworst)
{
	*array = (int*)malloc(sizeofworst * sizeof(int));
	int value = -1;
	for (int i = 0; i < sizeofworst; i++)
	{
		(*array)[i] = value;
		value -= 2;
	}
}
void array_free(int** array1, int** array2, int** array_worst1, int** array_worst2)
{
	free(*array1);
	free(*array2);
	free(*array_worst1);
	free(*array_worst2);
}