#pragma once
#include <iostream>

#include "student_teacher.h"

#define MENU_ERROR -1

enum Menu {
	MAN = 1,
	STUDENT,
	TEACHER,
	STUDENT_TEACHER,
	EXIT
};

int* input_marks();
int input_check();
void input_string_with_max_length(char* string, int limit);
void press_to_continue();
void print_menu();
void test_functionality();