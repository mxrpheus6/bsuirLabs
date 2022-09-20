#include <stdio.h>

int main(void) 
{
	int a, b, c, temp;
	printf("LAB 2 TASK 1 by Kazachenko Pavel from GROUP 250504\n\n");
	
	for (int i = 401; i < 500; i++)
	{
		a = i / 100;
		b = i / 10 % 10;
		c = i % 10;
		if (a + b + c == 9)
		{
			temp = c * 100 + b * 10 + a;
			if (i == temp * 47 / 36) 
			{
				printf("Answer is %d\n", i);
				return 0;
			}
		}
		else
		{
			continue;
		}
	}
	return 0;
}