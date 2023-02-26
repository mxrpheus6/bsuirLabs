#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "structeres.h"
#include "menu.h"

char** parseName(FILE* pointer);
float* parseDiag(FILE* pointer);
int* parseInt(FILE* pointer, int len);
void parse(Smartphone** array, FILE* pointer, int* size);