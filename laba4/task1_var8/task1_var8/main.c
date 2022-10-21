#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 12
#define N 100
#define M 100
int main(void)
{
	int numbers[N][M] = { {0}, {0} }, amountofrows, amountofcols, multiply, multiplycheck, sumofd1 = -2147483647, sumofd2 = -2147483647, sumofdtemp, amount;
	char number[MAX], strtemp[MAX], choice[MAX], check1[MAX] = "k ", check2[MAX] = "r ";
	printf("LAB 4 TASK 1 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter amount of rows and columns: ");
	fgets(number, MAX, stdin);
	while (isdigit(number) != TRUE || stringtoint(number) <= 1 || stringtoint(number) > 100)
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
	else if (compare(&choice, &check2) == TRUE)
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
	for (int i = 0; i < amountofrows; i++)
	{
		multiplycheck = 0;
		multiply = 1;
		for (int j = 0; j < amountofcols; j++)
		{
			if (numbers[i][j] >= 0)
			{
				multiplycheck++;
				multiply *= numbers[i][j];
			}
		}
		if (multiplycheck == amountofrows)
		{
			printf("\nThe result of multiplying numbers in %d row is %d\n", i + 1, multiply);
		}
		else
		{
			printf("\nThere are negative numbers in row %d\n", i + 1);
		}
	}
	for (int k = 1; k <= amountofrows - 1; k++)
	{
		for (int i = k; i <= amountofrows - 1; )
		{
			sumofdtemp = 0;
			for (int j = 0; j < amountofrows - 1; )				
			{
				sumofdtemp += numbers[i][j];
				i++;
				j++;
			}
			if (sumofdtemp > sumofd1)
			{
				sumofd1 = sumofdtemp;
			}
		}
	}
	for (int k = 1; k <= amountofrows - 1; k++)
	{
		for (int i = 0; i <= amountofrows - 2; )
		{
			sumofdtemp = 0;
			for (int j = k; j < amountofrows; )
			{
				sumofdtemp += numbers[i][j];
				i++;
				j++;
			}
			if (sumofdtemp > sumofd2)
			{
				sumofd2 = sumofdtemp;
			}
		}
	}
	if (sumofd1 > sumofd2)
	{
		printf("\nThe maximum among diagonals parallel to the main is %d\n\n", sumofd1);
	}
	else if (sumofd1 < sumofd2)
	{
		printf("\nThe maximum among diagonals parallel to the main is %d\n\n", sumofd2);
	}
	else if (sumofd1 == sumofd2)
	{
		printf("\nThere are several diagonals with the same sum that is %d\n\n", sumofd1);
	}
	for (int i = 0; i < amountofrows; i++)
	{
		for (int j = 0; j < amountofcols; j++)
		{
			printf(" %d ", numbers[i][j]);
		}
		printf("\n");
	}
	return 0;
}