#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#define TRUE 1
#define FALSE 0

int length(char* string)
{
	int i = 0;
	for (i; string[i] != '\0'; i++);
	return i - 1;
}
int compare(char* string1, char* string2)
{
	int len1, len2;
	len1 = length(string1);
	len2 = length(string2);
	if (len1 == len2)
	{
		for (int i = 0; i < len1; i++)
		{
			if (string1[i] != string2[i])
			{
				return FALSE;
			}
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
void array_input_keyboard(int* array, int size)
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
		array[i] = input;
	}
}
void array_input_random(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (rand() % 2 == 0)
		{
			array[i] = rand() % 100;
		}
		else
		{
			array[i] = -rand() % 100;
		}
	}
}
int array_min(int* array, int size)
{
	int min = *array;
	for (int i = 0; i < size; i++)
	{
		if (*(array + i) < min)
		{
			min = *(array + i);
		}
	}
	return min;
}
void array_output(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", *(array + i));
	}
}
void array_memory(int** array, int* sizeofarray, int min)
{
	for (int i = 0; i < (*sizeofarray); i++)
	{
		if ((*array)[i] == min)
		{
			for (int index = i; index < (*sizeofarray) - 1; index++)
			{
				(*array)[index] = (*array)[index + 1];
			}
			(*sizeofarray)--;
			*array = (int*)realloc(*array, (*sizeofarray) * sizeof(int));
			i--;
		}
	}
}
void array_start_memory(int** array, int sizeofarray)
{
	*array = (int*)malloc(sizeofarray * sizeof(int));
}
void array_choice(char* choice, char* check_k, char* check_r)
{
	int maxch = 12;
	printf("Do you want to fill the array from the keyboard or randomly? (k/r): ");
	fgets(choice, maxch, stdin);
	while (compare(choice, check_k) != TRUE && compare(choice, check_r) != TRUE)
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
void choice_compare(int** array, char* choice, char* check_k, int sizeofarray)
{
	if (compare(choice, check_k) == TRUE)
	{
		array_input_keyboard(*array, sizeofarray);
	}
	else
	{
		srand(time(NULL));
		array_input_random(*array, sizeofarray);
	}
}
void size_check(int sizeofarray)
{
	if (sizeofarray == 0)
	{
		printf("All numbers in array are the same\n");
		exit(0);
	}
}
void array_free(int** array)
{
	free(*array);
}