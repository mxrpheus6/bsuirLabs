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
	mergeSort(&indexes, 0, argc - 2);
	stringsOutput2(&strings, &indexes, argc);
	free(indexes);
	free(strings);
	return 0;
}