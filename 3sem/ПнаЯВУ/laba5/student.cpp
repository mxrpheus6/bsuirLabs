#include "student.h"

Student::Student() {
	for (int i = 0; i < MAX_MARKS_AMOUNT; i++) {
		marks[i] = -1;
	}
	scholarship = 0.0;
}

Student::Student(int* marks, double scholarship) {
	set_marks(marks);
	set_scholarship(scholarship);
}

Student::Student(char* first_name, char* last_name, int* marks, double scholarship) : Man(first_name, last_name) {
	set_marks(marks);
	set_scholarship(scholarship);
}

void Student::set_marks(int* marks) {
	if (sizeof(marks) / sizeof(marks[0]) > 20) {
		throw IntArrayException("Length of the marks array is more than permissible");
	}

	int i = 0;
	while (marks[i] != -1) {
		if (marks[i] < -1 || marks[i] > 10)
			throw IntException("Mark can't be less than zero and more than ten.");
		this->marks[i] = marks[i];
		i++;
	}
}

void Student::set_scholarship(double scholarship) {
	if (scholarship < 0.0) {
		throw DoubleException("Scholarship can't be less than zero.");
	}
	this->scholarship = scholarship;
}

const int* Student::get_marks() const{
	return marks;
}

const double Student::get_scholarship() const{
	return scholarship;
}

void Student::print_marks() const{
	std::cout << "[ ";
	for (int i = 0; i < MAX_MARKS_AMOUNT; i++) {
		if (marks[i] == -1) {
			break;
		}
		std::cout << marks[i] << ' ';
	}
	std::cout << ']';
}

void Student::learn() const {
	std::cout << Man::get_fisrt_name() << " has marks:";
	print_marks();
	std::cout << " and schloraship equals " << scholarship << std::endl;
}