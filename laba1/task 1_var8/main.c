#include <stdio.h>

int main(void) {
	float a, b, c, square, volume;
	printf("Enter edge a: ");
	scanf_s("%f", &a);
	printf("Enter edge b: ");
	scanf_s("%f", &b);
	printf("Enter edge c: ");
	scanf_s("%f", &c);
	square = 2 * (a * b + b * c + a * c);
	volume = a * b * c;
	printf("Square = %.3f\n", square);
	printf("Volume = %.3f\n", volume);
}