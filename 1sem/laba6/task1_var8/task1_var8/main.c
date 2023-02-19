#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arrays.h"
#include "sort.h"
#include "func.h"

#define MAXCH 12

int main(void)
{
	int sizeofarray, sizeofworst = 1000;
	double time;
	int* numbers1;
	int* numbers2;
	int* numbers_worst1;
	int* numbers_worst2;
	char choice[MAXCH], check_k[MAXCH] = "k ", check_r[MAXCH] = "r ";
	printf("LAB 6 TASK 1 by Kazachenko Pavel from GROUP 250504\n\n");
	array_choice(&choice, check_k, check_r);
	array_size(&sizeofarray);
	array_worst(&numbers_worst1, sizeofworst);
	array_worst(&numbers_worst2, sizeofworst);
	array_start_memory(&numbers1, &numbers2, sizeofarray);
	compare_choice(&numbers1, &numbers2, choice, check_k, sizeofarray);
	printf("\nArray before changes:\n\n");
	//array_output(&numbers1, sizeofarray);
	bubble_sort(numbers1, sizeofarray, &time);
	printf("\n\nArray after Bubble Sort:\n\n");
	//array_output(&numbers1, sizeofarray);
	printf("\n\nThe time of Bubble sort is %.3f (sec)\n\n", time);
	printf("Array before changes:\n\n");
	//array_output(&numbers2, sizeofarray);
	shell_sort(&numbers2, sizeofarray, &time);
	printf("\n\nArray after Shell Sort:\n\n");
	//array_output(&numbers2, sizeofarray);
	printf("\n\nThe time of Shell sort is %.3f (sec)\n\n", time);
	printf("\nWorst array before changes:\n\n");
	//array_output(&numbers_worst1, sizeofworst);
	bubble_sort(numbers_worst1, sizeofworst, &time);
	printf("\n\nWorst array after Bubble Sort:\n\n");
	//array_output(&numbers_worst1, sizeofworst);
	printf("\n\nThe time of Bubble sort is %.3f (sec)\n\n", time);
	printf("Worst array before changes:\n\n");
	//array_output(&numbers_worst2, sizeofworst);
	shell_sort(&numbers_worst2, sizeofworst, &time);
	printf("\n\nWorst array after Shell Sort:\n\n");
	//array_output(&numbers_worst2, sizeofworst);
	printf("\n\nThe time of Shell sort is %.3f (sec)\n\n", time);
	array_free(&numbers1, &numbers2, &numbers_worst1, &numbers_worst2);
	return 0;
}