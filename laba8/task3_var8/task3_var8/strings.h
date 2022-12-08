#pragma once
void getString(char** string);
int stringLength(char** string);
void stringsInput(char** strings, char** argv, int size);
void stringsOutput(char*** strings, int argc);
int wordCounter(char*** strings, int index);
int symCounter(char*** strings, int index);