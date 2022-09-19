#include <stdio.h>
int main(void) 
{
	int a, b, res;
	char sign;

	printf("LAB 1 TASK 4 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter operation (+, -, *, /): ");
	scanf_s("%c", &sign);
	if (sign != '+' && sign != '-' && sign != '*' && sign != '/') 
	{
		printf("\nWrong input. You must write correct operation.\n");
		return 0;
	}
	printf("Enter number a: ");
	if (scanf_s("%d", &a) == 0) 
	{
		printf("\nWrong input. You must write integer number.\n");
		return 0;
	}
	printf("Enter number b: ");
	if (scanf_s("%d", &b) == 0) 
	{
		printf("\nWrong input. You must write integer number.\n");
		return 0;
	}

	switch (sign) 
	{
	case '+':
		res = a + b;
		printf("\n%d + %d = %d\n", a, b, res);
		break;
	case '-':
		res = a - b;
		printf("\n%d - %d = %d\n", a, b, res);
		break;
	case '*':
		res = a * b;
		printf("\n%d * %d = %d\n", a, b, res);
		break;
	case '/':
		if (b == 0) 
		{
			printf("\nError. Division by zero.\n");
			return 0;
		}
		else 
		{
			double res = (double)a / (double)b;
			printf("\n%d / %d = %.2f\n", a, b, res);
			break;
		}
	default:
		printf("\nWrong input.You must write number.\n");
	}
	return 0;
}