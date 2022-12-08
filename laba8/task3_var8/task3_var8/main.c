#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "sort.h"

int main(int argc, char **argv) {
	char** strings;
	/*strings = (char**)malloc(argc);
	if (argc == 1) {
		printf("There is no arguments except file name!");
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		int len = stringLength(&argv[i]);
		strings[i - 1] = (char*)calloc(len, sizeof(char*));
		for (int j = 0; j < len; j++) {
			strings[i - 1][j] = argv[i][j];
		}
	}*/
	stringsInput(&strings, argv, argc);
	/*printf("Strings before sorting:\n");
	for (int i = 0; i < argc - 1; i++) {
		printf("[%d]%s\t%d\n", i + 1, strings[i], symCounter(&strings, i));
	}
	printf("\nString after sorting:\n");*/
	stringsOutput(&strings, argc);
	return 0;
}