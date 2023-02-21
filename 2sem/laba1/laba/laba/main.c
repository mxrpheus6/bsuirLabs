#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "structeres.h"
#include "menu.h"
#include "parser.h"

int main(void) {
	setlocale(LC_ALL, "Rus");
	Smartphone* telephone = NULL;
	int size = 0;
	FILE* pointer;
	fopen_s(&pointer, "D:/Work/html.txt", "r, ccs=UTF-8");
	parseName(pointer);
	parseDiag(pointer);	
	parseRam(pointer);
	parseMemory(pointer);
	parseCameraResolution(pointer);
	parseBattery(pointer);
	//mainMenu(&telephone, &size);
	//free(telephone);
	return 0;
}