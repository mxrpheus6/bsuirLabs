#include "comparators.h"

int compare(void* a, void* b) {
	return (*(unsigned char*)a - *(unsigned char*)b);
}