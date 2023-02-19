#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "input.h"
#include "output.h"

int main(void) {
	void (*function[3])(void) = { &task1, &task2, &task3 };
	int task;
	taskNum(&task);
	function[task - 1]();
	return 0;
}