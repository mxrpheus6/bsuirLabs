#include <stdio.h>
#include "myfunc.h"

int main(void) 
{
	printf("LAB 1 TASK 2 by Kazachenko Pavel from GROUP 250504\n\n");
	float x1, y1, x2, y2, x3, y3, a, b, c;
	printf("Enter coordinate x1 value:\n");
	if (scanf_s("%f", &x1) == 0) 
	{
		printf("Error. You must write number.");
		return 0;
	}
	printf("Enter coordinate y1 value:\n");
	if (scanf_s("%f", &y1) == 0) 
	{
		printf("Error. You must write number.");
		return 0;
	}
	printf("Enter coordinate x2 value:\n");
	if (scanf_s("%f", &x2) == 0) 
	{
		printf("Error. You must write number.");
		return 0;
	}
	printf("Enter coordinate y2 value:\n");
	if (scanf_s("%f", &y2) == 0) 
	{
		printf("Error. You must write number.");
		return 0;
	}
	printf("Enter coordinate x3 value:\n");
	if (scanf_s("%f", &x3) == 0) 
	{
		printf("Error. You must write number.");
		return 0;
	}
	printf("Enter coordinate y3 value:\n");
	if (scanf_s("%f", &y3) == 0) 
	{
		printf("Error. You must write number.");
		return 0;
	}
	a = my_sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	b = my_sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	c = my_sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));

	if (c < a + b && a < b + c && b < a + c)
	{
		if (a >= b && a >= c)
		{
			if (a * a == b * b + c * c)
			{
				printf("Rectangular triangle");
				return 0;
			}
			else if (a * a > b * b + c * c)
			{
				printf("Obtuse triangle");
				return 0;
			}
			else if (a * a < b * b + c * c)
			{
				printf("Acute Triangle");
				return 0;
			}
		}
		else if (b >= a && b >= c)
		{
			if (b * b == a * a + c * c)
			{
				printf("Rectangular triangle");
				return 0;
			}
			else if (b * b > a * a + c * c)
			{
				printf("Obtuse triangle");
				return 0;
			}
			else if (b * b < a * a + c * c)
			{
				printf("Acute Triangle");
				return 0;
			}
		}
		else if (c >= a && c >= b)
		{
			if (c * c == a * a + b * b)
			{
				printf("Rectangular triangle");
				return 0;
			}
			else if (c * c > a * a + b * b)
			{
				printf("Obtuse triangle");
				return 0;
			}
			else if (c * c < a * a + b * b)
			{
				printf("Acute Triangle");
				return 0;
			}
		}
		else
		{
			printf("Impossible triangle");
			return 0;
		}
	}
	else
	{
		printf("Impossible triangle");
		return 0;
	}
}