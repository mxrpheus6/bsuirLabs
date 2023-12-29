#include "student_teacher.h"

StudentTeacher::StudentTeacher() : Man(), Student(), Teacher() {
	amount_of_articles = 0;
}

StudentTeacher::StudentTeacher(char* first_name, char* last_name, double scholarship, double rate, double salary, int amount_of_articles) : Man(first_name, last_name), Student(scholarship), Teacher(rate, salary) {
	set_amount_of_articles(amount_of_articles);
}


void StudentTeacher::set_amount_of_articles(int amount_of_articles) {
	if (amount_of_articles < 0) {
		throw std::string("Amount of articles can't be less than zero.");
	}
	this->amount_of_articles = amount_of_articles;
}

const int StudentTeacher::get_amount_of_articles() const {
	return amount_of_articles;
}

double StudentTeacher::total_salary() {
	return Teacher::get_salary() + Teacher::get_rate();
}

void StudentTeacher::article_presentation() {
	std::cout << "Student and teacher " << Man::get_fisrt_name() << " " << Man::get_last_name() << " made " << amount_of_articles << " articles" << std::endl;
}