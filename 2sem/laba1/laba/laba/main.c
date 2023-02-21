#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "structeres.h"
#include "menu.h"

int main(void) {
	setlocale(LC_ALL, "Rus");
	Smartphone* telephone = NULL;
	int size = 0;
	mainMenu(&telephone, &size);
	free(telephone);
	return 0;
}