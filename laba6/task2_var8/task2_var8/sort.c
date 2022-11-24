#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "arrays.h"

shellSort(int*** array, int amountOfRows, int amountOfCols)
{
	int i, j, step, temp;
	for (step = amountOfCols / 2; step > 0; step /= 2)
	{
		for (int i = step; i < amountOfCols; i++)
		{
			temp = arrayMaxCol(array, amountOfRows, i);
			for (int j = i; j >= step; j -= step)
			{
				if (temp < arrayMaxCol(array, amountOfRows, j - step))
				{
					arrayColSwap(array, amountOfRows, j, j - step);
				}
				else
				{
					break;
				}
			}
		}
	}
}
