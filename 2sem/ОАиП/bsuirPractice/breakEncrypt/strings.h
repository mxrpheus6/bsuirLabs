#pragma once

int isLetter(char symbol);

void upperToLower(char* symbol);

void freqAnalysis(FreqDict** array, char** path);

void caesaerCipher(char* text, int shift, int mode);