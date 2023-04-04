#include "comparators.h"

int compare(const void* a, const void* b) {
	return (*(unsigned char*)a - *(unsigned char*)b);
}