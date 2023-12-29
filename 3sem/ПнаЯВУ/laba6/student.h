#pragma once
#include <iostream>

#include "man.h"

#define MAX_MARKS_AMOUNT 20

class Student : public virtual Man {
private:
	double scholarship;
public:
	Student();
	Student(double scholarship);
	Student(char* first_name, char* last_name, double scholarship);

	void set_scholarship(double scholarship);

	const double get_scholarship() const;

	void learn() const;
};