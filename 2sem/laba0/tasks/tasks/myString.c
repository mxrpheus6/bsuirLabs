#include <stdio.h>
#include "myString.h"

int isDigit(char* str) {
	int i = 0;
	while (str[i] != '\n') {
		if (str[i] == '\0')
			return 1;
		if (str[i] < 47 || str[i] > 57) {
			return 0;
		}
		i++;
	}
	return 1;
}