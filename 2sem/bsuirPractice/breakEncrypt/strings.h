#pragma once

#include <stdio.h>
#include <string.h>

#include "bool.h"
#include "structures.h"
#include "files.h"

typedef struct FreqDict FreqDict;

int isLetter(char symbol);

void upperToLower(char* symbol);

void freqAnalysis(FreqDict** array, char** path);

void caesaerCipher(char* text, int shift, int mode);