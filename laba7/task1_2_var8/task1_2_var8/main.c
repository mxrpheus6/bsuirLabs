#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "tasks.h"
#include "intput.h"

int main(void) {
	int num;
	void (*function[2])(void) = { &task1, &task2 };
	taskNum(&num);
	function[num - 1]();
	return 0;
}