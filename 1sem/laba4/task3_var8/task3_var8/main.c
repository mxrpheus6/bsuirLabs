#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 12
#define N 100
#define M 100
int main(void)
{
	int numbers[N][M] = { {0}, {0} }, amountofrows, amountofcols, max;
	char number[MAX], strtemp[MAX], choice[MAX], check1[MAX] = "k ", check2[MAX] = "r ";
	printf("LAB 4 TASK 3 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter amount of rows and columns: ");
	fgets(number, MAX, stdin);
	while (isdigit(number) != TRUE || stringtoint(number) < 1 || stringtoint(number) > 100)
	{
		printf("Invalid input. Enter correct number: ");
		fgets(number, MAX, stdin);
	}
	amountofrows = stringtoint(number);
	amountofcols = stringtoint(number);
	printf("Do you want to fill the array from the keyboard or randomly? (k/r): ");
	fgets(choice, MAX, stdin);
	while (compare(&choice, &check1) != TRUE && compare(&choice, &check2) != TRUE)
	{
		printf("Invalid input. Enter correct answer (k/r): ");
		fgets(choice, MAX, stdin);
	}
	if (compare(&choice, &check1) == TRUE)
	{
		for (int i = 0; i < amountofrows; i++)
		{
			printf("\nInput elements in row number %d\n\n", i + 1);
			for (int j = 0; j < amountofcols; j++)
			{
				printf("Input element %d: ", j + 1);
				fgets(strtemp, MAX, stdin);
				while (isdigit(strtemp) != TRUE)
				{
					printf("Invalid input. Enter correct element %d: ", j + 1);
					fgets(strtemp, MAX, stdin);
				}
				numbers[i][j] = stringtoint(strtemp);
			}
		}
	}
	if (compare(&choice, &check2) == TRUE)
	{
		srand(time(NULL));
		for (int i = 0; i < amountofrows; i++)
		{
			for (int j = 0; j < amountofcols; j++)
			{
				numbers[i][j] = signedrand();
			}
		}
	}
	max = numbers[0][0];
	for (int i = 0; i < amountofrows; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i <= amountofrows - j - 1 && numbers[i][j] % 2 != 0)
			{
				if (numbers[i][j] > max)
				{
					max = numbers[i][j];
				}
			}
		}
	}
	if (max % 2 != 0)
	{
		printf("\nMaximum odd number in the 4th sector is %d\n\n", max);
	}
	else
	{
		printf("\nThere is no odd numbers in the 4th sector\n\n", max);
	}
	for (int i = 0; i < amountofrows; i++)
	{
		for (int j = 0; j < amountofcols; j++)
		{
			printf("\t%d", numbers[i][j]);
		}
		printf("\n");
	}
	return 0;
}