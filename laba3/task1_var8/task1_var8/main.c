#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 12

int main(void)
{
	printf("LAB 3 TASK 1 by Kazachenko Pavel from GROUP 250504\n\n");
	int numbers[100] = { 0 }, amount, counter = 0, total = 0;
	char k[MAX], strtemp[MAX], choice[MAX], check1[MAX] = "k ", check2[MAX] = "r ", checkzero = 0;
	printf("Enter amount of numbers: ");
	fgets(k, MAX, stdin);
	while (isdigit(k) != 1 || stringtoint(k) < 0 || stringtoint(k) > 100)
	{
		printf("Invalid input. Enter correct number: ");
		fgets(k, MAX, stdin);
	}
	amount = stringtoint(k);
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
	else if (compare(&choice, &check2) == 1)
	{		
		srand(time(NULL));
		for (int i = 0; i < amount; i++)
		{
			numbers[i] = signedrand();
		}
	}
	for (int i = 0; i < amount; i++)
	{
		if (numbers[i] > 0)
		{
			counter++;
		}
		if (numbers[i] == 0)
		{
			checkzero++;
		}
	}
	if (checkzero == 0)
	{
		printf("\nAmount of positive elements equals %d", counter);
		printf("\n\nThere is no zeros.\n\n");
		for (int i = 0; i < amount; i++)
		{
			printf("%d ", numbers[i]);
		}
		return 0;
	}
	for (int i = amount - 1; i >= 0; i--)
	{
		if (numbers[i] == 0)
		{
			break;
		}
		total += numbers[i];
	}
	printf("\nAmount of positive elements equals %d", counter);
	printf("\n\nTotal equals %d\n\n", total);
	for (int i = 0; i < amount; i++)
	{
		printf("%d ", numbers[i]);
	}
	return 0;
}