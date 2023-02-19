#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#include "sort.h"

#define MAXCH 12

int main(void)
{
	int amountOfRows, amountOfCols;
	int** numbers;
	char choice[MAXCH], checkingK[MAXCH] = "k ", checkingR[MAXCH] = "r ";
	printf("LAB 6 TASK 2 by Kazachenko Pavel from GROUP 250504\n\n");
	arraySize(&amountOfRows, &amountOfCols);
	arrayInputKeyboard(&numbers, amountOfRows, amountOfCols);
	printf("\nArray before changes:\n\n");
	arrayOutput(&numbers, amountOfRows, amountOfCols);
	printf("\nArray after changes:\n\n");
	shellSort(&numbers, amountOfRows, amountOfCols);
	arrayOutput(&numbers, amountOfRows, amountOfCols);
	arrayFree(&numbers, amountOfRows);
	return 0;
}