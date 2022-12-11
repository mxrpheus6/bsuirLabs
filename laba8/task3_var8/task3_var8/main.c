#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "sort.h"

int main(int argc, char **argv) {
	char** strings;
	int** indexes;
	stringsInput(&strings, argv, argc);
	stringsOutput1(&strings, argc);
	prototype(&strings, &indexes, argc);
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%d\t", indexes[i][j]);
		}
		printf("||");
	}
	printf("\n\n");*/
	mergeSort(&indexes, 0, argc - 2);
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			printf("%d\t", indexes[i][j]);
		}
		printf("||");
	}*/
	//stringsOutput(&strings, argc);
	printf("\n\n");
	//resultArrayOfStrings(&strings, &indexes, argc);
	stringsOutput2(&strings, &indexes, argc);
	return 0;
}