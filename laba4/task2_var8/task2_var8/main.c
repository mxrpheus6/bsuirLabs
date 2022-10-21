#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 12
#define N 100
#define M 100
int main(void)
{
	float numbers[N][M] = { {0}, {0} }, doubletemp;
	int amountofrows, amountofcols, zerocheck, numberofchange, outputcheck = 0;
	char number[MAX], strtemp[MAX], choice[MAX], check1[MAX] = "k ", check2[MAX] = "r ";
	printf("LAB 4 TASK 2 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter amount of rows: ");
	fgets(number, MAX, stdin);
	while (isdigit(number) != TRUE || stringtoint(number) < 1 || stringtoint(number) > 100)
	{
		printf("Invalid input. Enter correct number: ");
		fgets(number, MAX, stdin);
	}
	amountofrows = stringtoint(number);
	printf("Enter amount of columns: ");
	fgets(number, MAX, stdin);
	while (isdigit(number) != TRUE || stringtoint(number) < 1 || stringtoint(number) > 100)
	{
		printf("Invalid input. Enter correct number: ");
		fgets(number, MAX, stdin);
	}
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
				while (scanf_s(" %f", &doubletemp) != 1 || getchar() != '\n')
				{
					printf("Invalid input. Enter correct element %d: ", j + 1);
					rewind(stdin);
				}
				numbers[i][j] = doubletemp;
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
				numbers[i][j] = (double)signedrand() / 10.0;
			}
		}
	}
	for (int i = 0; i < amountofrows; i++)
	{
		zerocheck = 0;
		for (int j = 0; j < amountofcols; j++)
		{
			if (numbers[i][j] == 0)
			{
				zerocheck++;
			}
			else
			{
				break;
			}
		}
		if (zerocheck == amountofcols)
		{
			numberofchange = i;
			outputcheck++;
			for (int k = 0; k < amountofrows; k++)
			{
				numbers[k][i] = numbers[k][i] / 2.0;
			}
			break;
		}
	}
	if (outputcheck == 0)
	{
		printf("\nThere is no rows that are full of zeros\n");
	}
	else if (amountofrows > amountofcols && numberofchange >= amountofcols)
	{
		printf("\nNumber of row is bigger than number of columns\n");
	}
	printf("\n");
	for (int i = 0; i < amountofrows; i++)
	{
		for (int j = 0; j < amountofcols; j++)
		{
			printf(" %.2f ", numbers[i][j]);
		}
		printf("\n");
	}
	return 0;
}