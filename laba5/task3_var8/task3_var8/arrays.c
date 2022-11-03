#include <stdio.h>
#define TRUE 0
#define FALSE 1

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
	for (int i = 0; i < amountofrows; i++)
	{
		if (*(*(array + i) + j) > -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}
void array_delete(int** array, int amountofrows, int* amountofcols, int k)
{
	for (int i = 0; i < amountofrows; i++)
	{
		for (int j = k; j + 1 < (*amountofcols); j++)
		{
			*(*(array + i) + j) = *(*(array + i) + j + 1);
		}
	}
	(*amountofcols)--;
}