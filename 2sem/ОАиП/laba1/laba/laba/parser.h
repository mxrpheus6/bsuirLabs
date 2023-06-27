#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "structeres.h"
#include "menu.h"

typedef enum {
    MEMORY = 34,
    RAM = 36,
    BATTERY = 40
} ParseTypes;

char** parseChar(FILE* pointer);
float* parseFloat(FILE* pointer);
int* parseInt(FILE* pointer, int len);
void parse(Smartphone** array, FILE* pointer, int* size);