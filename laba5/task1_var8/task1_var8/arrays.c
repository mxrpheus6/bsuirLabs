#define TRUE 1
#define FALSE 0
#include <stdio.h>

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
			min =  *(array + i);
		}
	}
	return min;
}
void array_move(int* array, int* size, int index)
{
	for (int i = index; i < (*size) - 1; i++)
	{
		*(array + i) = *(array + i + 1);
	}
	(*size)--;
}
void array_output(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d\t", *(array + i));
	}
}