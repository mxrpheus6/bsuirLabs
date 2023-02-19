#include<stdio.h>



typedef struct Car {
	const char* name;
	int skor;
	const char* color;
}Car;

void output(Car* pointer) {
	printf("%s", pointer->name);
	printf("%d", pointer->skor);
	printf("%s", pointer->color);
}

int main() {
	Car BMW;
	Car* p = &BMW;
	char name_bmw[10] = "BMW M8";
	BMW.name = name_bmw;
	BMW.skor = 200;
	BMW.color = "red";
	output(p);
	return 0;
}