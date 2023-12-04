#pragma once
#include <iostream>

#include "man.h"

class Teacher : public virtual Man {
private:
	double rate;
	double salary;
public:
	Teacher();
	Teacher(double rate, double salary);
	Teacher(char* first_name, char* last_name, double rate, double salary);

	void set_rate(double rate);
	void set_salary(double salary);

	const double get_rate() const;
	const double get_salary() const;

	void earning() const;
};