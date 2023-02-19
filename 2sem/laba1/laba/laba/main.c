#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "structeres.h"
#include "menu.h"

int main(void) {
	setlocale(LC_ALL, "Rus");
	Smartphone* iphone = NULL;
	int size;
	mainMenu(&iphone, &size);
	free(iphone);
	return 0;
}