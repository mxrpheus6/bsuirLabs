#pragma once
#include <iostream>

#include "teacher.h"
#include "student.h"

class StudentTeacher : public Student, public Teacher {
private:
	int amount_of_articles;
public:
	StudentTeacher();
	StudentTeacher(char* first_name, char* last_name, double scholarship, double rate, double salary, int amount_of_articles);

	void set_amount_of_articles(int amoint_of_articles);

	const int get_amount_of_articles() const;
	double total_salary();
	void article_presentation();
};