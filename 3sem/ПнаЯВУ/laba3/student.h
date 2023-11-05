#pragma once
#include <iostream>

#include "man.h"

#define MAX_MARKS_AMOUNT 20

class Student : public virtual Man {
private:
	int marks[MAX_MARKS_AMOUNT];
	double scholarship;
public:
	Student();
	Student(int* marks, double scholarship);
	Student(char* first_name, char* last_name, int* marks, double scholarship);

	void set_marks(int* marks);
	void set_scholarship(double scholarship);

	const int* get_marks() const;
	const double get_scholarship() const;

	void print_marks() const;

	void learn() const;
};