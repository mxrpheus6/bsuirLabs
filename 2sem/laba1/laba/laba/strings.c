#include <stdio.h>

int strlen_n(char* string) {
	int i = 0;
	while (string[i] != '\n') {
		i++;
	}
	i++;
	return i;
}