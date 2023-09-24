#pragma once

#include <iostream>

#include "square.h"

enum Menu {
	SET = 1,
	PRINT_AREA,
	PRINT_PERIMETER,
	EXIT
};

void print_menu();
int input_check();
void press_to_continue();