#include "menu.h"

int* input_marks() {
	int* marks = new int[MAX_MARKS_AMOUNT];
	int i = 0;
	int temp;
	while (true) {
		if (i > 19) {
			throw IntArrayException("Length of the marks array is more than permissible");
		}
		std::cout << "Enter mark " << i + 1 << ":";
		std::cin >> temp;
		if (temp == -1) {
			marks[i] = temp;
			break;
		}
		marks[i] = temp;
		i++;
	}
	return marks;
}

int input_check() {
	double input;
	while (!(std::cin >> input) || std::cin.peek() != '\n') {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Invalid error. You must enter integer number." << std::endl;
	}
	return input;
}

void input_string_with_max_length(char* str, int max_length) {
	std::cin.getline(str, max_length);

	if (strlen(str) >= max_length - 1)
		throw CharArrayException("Length is more than available");
}


void press_to_continue() {
	std::cout << "Press enter to continue...";
	std::cin.ignore();
	std::cin.get();
}

void print_menu()
{
	std::cout << "MENU" << std::endl
		<< "1) - Action of Man" << std::endl
		<< "2) - Action of Student" << std::endl
		<< "3) - Action of Teacher" << std::endl
		<< "4) - Action of Student-teacher" << std::endl
		<< "5) - Exit" << std::endl
		<< "Your choose: ";
}

void test_functionality()
{
	StudentTeacher student_teacher;

	char first_name[MAX_NAME_LENGTH];
	std::cout << "Enter first name:";
	try {
		input_string_with_max_length(first_name, MAX_NAME_LENGTH);
	}
	catch (Exception &e) {
		e.show();
		exit(-1);
	}

	char last_name[MAX_NAME_LENGTH];
	std::cout << "Enter last name:";
	try {
		input_string_with_max_length(last_name, MAX_NAME_LENGTH);
	}
	catch (Exception& e) {
		e.show();
		exit(-1);
	}

	try
	{
		student_teacher.set_first_name(first_name);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}

	try
	{
		student_teacher.set_last_name(last_name);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}

	int* marks;
	std::cout << "Enter marks:" << std::endl;
	try {
		marks = input_marks();
	}
	catch (Exception& e) {
		e.show();
		exit(-1);
	}
	rewind(stdin);

	try
	{
		student_teacher.set_marks(marks);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}


	double scholarship;
	std::cout << "Enter scholarship:";
	std::cin >> scholarship;
	rewind(stdin);

	try
	{
		student_teacher.set_scholarship(scholarship);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}

	double rate;
	std::cout << "Enter rate:";
	std::cin >> rate;
	rewind(stdin);

	try
	{
		student_teacher.set_rate(rate);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}



	double salary;
	std::cout << "Enter salary:";
	std::cin >> salary;
	rewind(stdin);

	try
	{
		student_teacher.set_salary(salary);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}

	int amount_of_articles;
	std::cout << "Enter amount of articles:";
	std::cin >> amount_of_articles;
	rewind(stdin);

	try
	{
		student_teacher.set_amount_of_articles(amount_of_articles);
	}
	catch (Exception& e)
	{
		e.show();
		exit(-1);
	}


	int choose = 0;

	while (choose != EXIT) {
		system("cls");
		print_menu();
		choose = input_check();

		switch (choose) {
			case MAN:
			{
				student_teacher.speak();
				press_to_continue();
				break;
			}
			case STUDENT:
			{
				student_teacher.learn();
				press_to_continue();
				break;
			}
			case TEACHER:
			{
				student_teacher.earning();
				press_to_continue();
				break;
			}
			case STUDENT_TEACHER:
			{
				student_teacher.article_presentation();
				press_to_continue();
				break;
			}
			case EXIT:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
}