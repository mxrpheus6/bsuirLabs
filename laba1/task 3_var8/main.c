#include <stdio.h>
#include "myfunc.h"

int main(void) 
{
	printf("LAB 1 TASK 3 by Kazachenko Pavel from GROUP 250504\n\n");
	float x, y, hypotenuse, r = 1.0;
	printf("Enter coordinate x = ");
	if (scanf_s("%f", &x) == 0) 
	{
		printf("Error. You must write number.\n");
		return 0;
	}
	else if (x == 0)
	{
		printf("Point does not belong to the top of the circle.\n");
		return 0;
	}
	printf("Enter coordinate y = ");
	if (scanf_s("%f", &y) == 0) 
	{
		printf("Error. You must write number.\n");
		return 0;
	}
	else if (y < 0)
	{
		printf("Point does not belong to the top of the circle.\n");
		return 0;
	}

	hypotenuse = my_sqrt(x * x + y * y);
	if (hypotenuse < r) 
	{
		printf("Point belongs to the top of the circle.\n");
	}
	else 
	{
		printf("Point does not belong to the top of the circle.\n");
	}
	return 0;
}
