#include <stdio.h>
int main(void)
{
	printf("LAB 1 TASK 1 by Kazachenko Pavel from GROUP 250504\n\n");
	float a, b, c, square, volume;
	printf("Enter edge a: ");
	if (scanf_s("%f", &a) == 0)
	{
		printf("Error. You must write number.\n");
		return 0;
	}
	else if (a <= 0)
	{
		printf("Error. Side length always greater than zero.\n");
		return 0;
	}
	printf("Enter edge b: ");
	if (scanf_s("%f", &b) == 0)
	{
		printf("Error. You must write number.\n");
		return 0;
	}
	else if (b <= 0)
	{
		printf("Error. Side length always greater than zero.\n");
		return 0;
	}
	printf("Enter edge c: ");
	if (scanf_s("%f", &c) == 0)
	{
		printf("Error. You must write number.\n");
		return 0;
	}
	if (c <= 0)
	{
		printf("Error. Side length always greater than zero.\n");
		return 0;
	}
	square = 2 * (a * b + b * c + a * c);
	volume = a * b * c;
	printf("Square = %.3f\n", square);
	printf("Volume = %.3f\n", volume);
	return 0;
}


