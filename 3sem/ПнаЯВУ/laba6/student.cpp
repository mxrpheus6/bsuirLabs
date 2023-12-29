#include "student.h"

Student::Student() {
	scholarship = 0.0;
}

Student::Student(double scholarship) {
	set_scholarship(scholarship);
}

Student::Student(char* first_name, char* last_name, double scholarship) : Man(first_name, last_name) {
	set_scholarship(scholarship);
}

void Student::set_scholarship(double scholarship) {
	if (scholarship < 0.0) {
		throw std::string("Scholarship can't be less than zero.");
	}
	this->scholarship = scholarship;
}

const double Student::get_scholarship() const{
	return scholarship;
}

void Student::learn() const {
	std::cout << Man::get_fisrt_name() << " schloraship equals " << scholarship << std::endl;
}