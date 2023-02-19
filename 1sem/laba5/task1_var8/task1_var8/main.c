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
	array_choice(&choice, check_k, check_r);
	array_size(&sizeofarray);
	array_start_memory(&numbers, sizeofarray);
	choice_compare(&numbers, choice, check_k, sizeofarray);
	printf("Array without changes:\n\n");
	array_output(numbers, sizeofarray);
	min = array_min(numbers, sizeofarray);
	array_memory(&numbers, &sizeofarray, min);
	printf("\n\nArray after changes:\n\n");
	size_check(sizeofarray);
	array_output(numbers, sizeofarray);
	printf("\n");
	array_free(&numbers);
	return 0;
}