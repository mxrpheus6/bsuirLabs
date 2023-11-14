#include <iostream>

#include "teacher.h"

Teacher::Teacher() {
	rate = 0.0;
	salary = 0.0;
}

Teacher::Teacher(double rate, double salary) {
	set_rate(rate);
	set_salary(salary);
}

Teacher::Teacher(char* first_name, char* last_name, double rate, double salary) : Man(first_name, last_name) {
	set_rate(rate);
	set_salary(salary);
}

void Teacher::set_rate(double rate) {
	if (rate <= 0.0) {
		throw DoubleException("Rate can't be less or equal zero.");
	}
	this->rate = rate;
}

void Teacher::set_salary(double salary) {
	if (salary <= 0.0) {
		throw DoubleException("Salary can't be less or equal zero.");
	}
	this->salary = salary;
}

const double Teacher::get_rate() const {
	return rate;
}

const double Teacher::get_salary() const {
	return salary;
}

void Teacher::earning() const{
	std::cout << Man::get_fisrt_name() << " has rate " << rate << " and salary " << salary << std::endl;
}