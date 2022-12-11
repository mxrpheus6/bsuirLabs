#pragma once
int stringLength(char** string);
void stringsInput(char** strings, char** argv, int size);
void stringsOutput1(char*** strings, int argc);
void stringsOutput2(char*** strings, int*** indexes, int argc);
int wordCounter(char*** strings, int index);
int symCounter(char*** strings, int index);
int evenCheck(int*** strings, int index);
void prototype(char*** strings, int*** indexes, int argc);
void resultArrayOfStrings(char*** strings, int*** indexes, int argc);