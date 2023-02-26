#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "structeres.h"
#include "menu.h"
#include "parser.h"

int main(void) {
	Smartphone* telephone = NULL;
	int size = 0;
	int flag = 0;
	FILE* pointer;
	fopen_s(&pointer, "D:/Work/test228.txt", "r");
	mainMenu(&telephone, &size, pointer);
	free(telephone);
	fclose(pointer);
	return 0;
}