#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 12

int main(void)
{
	printf("LAB 3 TASK 3 by Kazachenko Pavel from GROUP 250504\n\n");
	int numbers[100] = { 0 }, amount, max = 0, count = 0, tempcount, general_count = 0, tempmax = 0;
	char n[MAX], strtemp[MAX], choice[MAX], check1[MAX] = "k ", check2[MAX] = "r ";
	printf("Enter amount of numbers: ");
	fgets(n, MAX, stdin);
	while (isdigit(n) != 1 || stringtoint(n) <= 0 || stringtoint(n) > 100)
	{
		printf("Invalid input. Enter correct number: ");
		fgets(n, MAX, stdin);
	}
	amount = stringtoint(n);
	printf("Do you want to fill the array from the keyboard or randomly? (k/r): ");
	fgets(choice, MAX, stdin);
	while (compare(&choice, &check1) != 1 && compare(&choice, &check2) != 1)
	{
		printf("Invalid input. Enter correct answer (k/r): ");
		fgets(choice, MAX, stdin);
	}
	if (compare(&choice, &check1) == 1)
	{
		for (int i = 0; i < amount; i++)
		{
			printf("Input element %d: ", i + 1);
			fgets(strtemp, MAX, stdin);
			while (isdigit(strtemp) != 1)
			{
				printf("Invalid input. Enter correct element %d: ", i + 1);
				fgets(strtemp, MAX, stdin);
			}
			numbers[i] = stringtoint(strtemp);
		}
	}
	if (compare(&choice, &check2) == 1)
	{
		srand(time(NULL));
		for (int i = 0; i < amount; i++)
		{
			numbers[i] = signedrand();
		}
	}

	for (int i = 0; i < amount - 1; i++)
	{
		for (int j = 0; j < amount - i - 1; j++)
		{
			if (numbers[j] > numbers[j + 1])
			{
				int arrtemp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = arrtemp;
			}
		}
	}
	for (int i = 0; i < amount; i++)
	{
		tempcount = 0;
		for (int j = 0; j < amount; j++)
		{
			if (numbers[i] == numbers[j] && numbers[i] % 2 == 0)
			{
				tempcount++;
			}
		}
		if (tempcount > count)
		{
			count = tempcount;
			max = i;
		}
	}
	if (count == 0)
	{
		printf("\nThere is no even numbers\n");
		return 0;
	}
	general_count = count;

	for (int i = 0; i < amount; i++)
	{
		if (numbers[i] % 2 == 0)
		{
			if (numbers[i] == numbers[i + 1])
			{
				tempmax++;
			}
			else 
			{
				tempmax++;
				if (general_count == tempmax)
				{
					printf("\nThe most common even number is %d (%d times)\n", numbers[i], general_count);
				}
				tempmax = 0;
			}
		}

	}
	printf("\n");
	for (int i = 0; i < 100; i++)
	{
		printf(" %d ", numbers[i]);
	}
	return 0;
}