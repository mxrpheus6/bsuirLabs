#include "structeres.h"

int isLetter(char symbol) {
	if ((symbol > 64 && symbol < 91 || symbol > 96 && symbol < 123)) {
		return TRUE;
	}
	return FALSE;
} 