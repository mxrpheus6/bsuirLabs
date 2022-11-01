#include <stdio.h>

void array_move(int** array, int i, int j)
{
	for (; *(*(array + i) + j) != -1; j++)
		*(*(array + i) + j) = *(*(array + i) + j + 1);
}
void array_output(int** array, int rows, int cols)
{
	printf("\n");
	for (int i = 0; i < rows; i++)
	{
		cols = 1;
		for (int j = 0; j < cols; j++)
		{
			if (array[i][j] != -1)
			{
				printf("%d\t", array[i][j]);
				cols++;
			}
		}
		printf("%d\n", -1);
	}
}
void array_cols_amount(int* array, int* size)
{
	int total = 1;
	for (int i = 0; i < total; i++)
	{
		if (array[i] != -1)
		{
			total++;
		}
	}
	(*size) = total;
}