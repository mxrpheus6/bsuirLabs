#include <stdio.h>

int main(void) 
{
	int a;
	printf("LAB 2 TASK 2 by Kazachenko Pavel from GROUP 250504\n\n");
	printf("Enter number a: ");
	scanf_s("%d", &a);
	for (; a < 1000000 ; )
	{
		a = a * a + 1;
	}
	printf("\nResult is %d\n", a);
	return 0;
}