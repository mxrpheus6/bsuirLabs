#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX 12

int main(void)
{
	printf("LAB 3 TASK 2 by Kazachenko Pavel from GROUP 250504\n\n");
	int numbers[100] = { 0 }, amount, before;
	char k[MAX], amountofnum[MAX], strtemp[MAX], choice[MAX], check1[MAX] = "k ", check2[MAX] = "r ";
	printf("Enter amount of numbers: ");
	fgets(amountofnum, MAX, stdin);
	while (isdigit(amountofnum) != 1 || stringtoint(amountofnum) <= 0 || stringtoint(amountofnum) >= 100)
	{
		printf("Invalid input. Enter correct number: ");
		fgets(amountofnum, MAX, stdin);
	}
	amount = stringtoint(amountofnum);
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
	printf("Which number to insert before: ");
	fgets(k, MAX, stdin);
	while (isdigit(k) != 1 || stringtoint(k) <= 0 || stringtoint(k) > 100 || (amount + amount) / stringtoint(k) > 100 )
	{
		printf("Invalid input. Enter correct number: ");
		fgets(k, MAX, stdin);
	}
	before = stringtoint(k);
	for (int i = before - 1; i < amount; i = i + before + 1)
	{
		for (int j = amount - 1; j >= i; j--)
		{
			numbers[j + 1] = numbers[j];
		}
		numbers[i] = 0;
		amount++;
	}
	for (int i = 0; i < 100; i++)
	{
		printf(" %d ", numbers[i]);
	}
	return 0;
}