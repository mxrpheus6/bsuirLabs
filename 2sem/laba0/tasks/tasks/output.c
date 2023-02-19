#include <stdio.h>
#include "output.h"

void printFile(char* path) {
	FILE* out;
	char ch;
	fopen_s(&out, path, "r");
	if (out == NULL) {
		printf("Oops... Something went wrong. It's not possible to open the file.");
		exit(1);
	}
	while ((ch = getc(out)) != EOF)
		printf("%c", ch);
}