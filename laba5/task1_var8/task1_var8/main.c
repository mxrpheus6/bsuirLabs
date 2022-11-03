#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#define MAXCH 12
int main(void)
{
	int sizeofarray, min, check_of_amount = 0;
	int* numbers;
	char choice[MAXCH], check_k[MAXCH] = "k ", check_r[MAXCH] = "r ";
	printf("LAB 5 TASK 1 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Do you want to fill the array from the keyboard or randomly? (k/r): ");
	fgets(choice, MAXCH, stdin);
	while (compare(&choice, &check_k) != TRUE && compare(&choice, &check_r) != TRUE)
	{
		printf("Invalid input. Enter correct answer (k/r): ");
		fgets(choice, MAXCH, stdin);
	}
	printf("Enter size of array: ");
	while (scanf_s(" %d", &sizeofarray) == 0 || getchar() != '\n' || sizeofarray < 1)
	{
		printf("Invalid input. Enter correct size of array: ");
		rewind(stdin);
	}
	numbers = (int*)malloc(sizeofarray * sizeof(int));
	if (compare(&choice, &check_k) == TRUE)
	{
		array_input_keyboard(numbers, sizeofarray);
	}
	else
	{
		srand(time(NULL));
		array_input_random(numbers, sizeofarray);
	}
	printf("Array without changes:\n\n");
	array_output(numbers, sizeofarray);
	min = array_min(numbers, sizeofarray);
	for (int i = 0; i < sizeofarray; i++)
	{
		if (*(numbers + i) == min)
		{
			array_move(numbers, &sizeofarray, i);
			numbers = (int*)realloc(numbers, sizeofarray * sizeof(int));
			i--;
		}
	}
	printf("\n\nArray after changes:\n\n");
	if (sizeofarray == 0)
	{
		printf("All numbers in array are the same");
		return 0;
	}
	array_output(numbers, sizeofarray);
	printf("\n");
	free(numbers);
	return 0;
}