#include <stdio.h>

int main(void)
{
	int f1 = 1, f2 = 1, temp, n;
	printf("LAB 2 TASK 3 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter N: ");
	scanf_s("%d", &n);
	for (; f2 <= n ; )
	{
		temp = f2;
		f2 = f1 + f2;
		f1 = temp;
	}
	printf("\nResult is %d\n", f2);
}