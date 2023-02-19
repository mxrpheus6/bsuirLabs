#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

int negarive_odd_index(int* array, int s)
{
	int counter = -1;
	for (int i = 0; ; i++)
	{
		if (array[i] % 2 == -1)
		{
			counter++;
			if (counter == s)
			{
				return i;
			}
		}
	}
}
int amount_of_negative_odds(int* array, int sizeofarray)
{
	int counter = 0;
	for (int i = 0; i < sizeofarray; i++)
	{
		if (array[i] % 2 == -1)
		{
			counter++;
		}
	}
	return counter;
}
void bubble_sort(int* array, int sizeofarray, double* time)
{
	double begin = clock();
	int odds = amount_of_negative_odds(array, sizeofarray);
	for (int i = 0; i < odds - 1; i++)
	{
		for (int j = 0; j < odds - i - 1; j++)
		{
			if (array[negarive_odd_index(array, j)] > array[negarive_odd_index(array, j + 1)])
			{
				int array_temp = array[negarive_odd_index(array, j)];
				array[negarive_odd_index(array, j)] = array[negarive_odd_index(array, j + 1)];
				array[negarive_odd_index(array, j + 1)] = array_temp;
			}
		}
	}
	double end = clock();
	*time = (end - begin) / CLOCKS_PER_SEC;
}
void shell_sort(int** array, int sizeofarray, double* time)
{
	double begin = clock();
	int odds = amount_of_negative_odds(*array, sizeofarray);
	int i, j, step, temp;
	for (step = odds; step > 0; step /= 2)
	{
		for (i = step; i < odds; i++)
		{
			temp = (*array)[negarive_odd_index(*array, i)];
			for (j = i; j >= step; j -= step)
			{
				if (temp < (*array)[negarive_odd_index(*array, j - step)])
				{
					(*array)[negarive_odd_index(*array, j)] = (*array)[negarive_odd_index(*array, j - step)];
				}
				else
				{
					break;
				}
			}
			(*array)[negarive_odd_index(*array, j)] = temp;
		}
	}
	double end = clock();
	*time = (end - begin) / CLOCKS_PER_SEC;
}
