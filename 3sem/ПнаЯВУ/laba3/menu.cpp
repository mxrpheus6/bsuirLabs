#include "menu.h"

int* input_marks() {
	int* marks = new int[MAX_MARKS_AMOUNT];
	int i = 0;
	int temp;
	while (i < MAX_MARKS_AMOUNT) {
		std::cout << "Enter number " << i << ":";
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
	while (true) {
		std::cin.getline(str, max_length);

		if (strlen(str) >= max_length - 1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Length is more than available" << std::endl << "Enter correct string:";
		}
		else {
			break;
		}
	}
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
	input_string_with_max_length(first_name, MAX_NAME_LENGTH);

	char last_name[MAX_NAME_LENGTH];
	std::cout << "Enter last name:";
	input_string_with_max_length(last_name, MAX_NAME_LENGTH);

	int* marks;
	std::cout << "Enter marks:" << std::endl;
	marks = input_marks();
	rewind(stdin);

	double scholarship;
	std::cout << "Enter scholarship:";
	std::cin >> scholarship;
	rewind(stdin);

	double rate;
	std::cout << "Enter rate:";
	std::cin >> rate;
	rewind(stdin);

	double salary;
	std::cout << "Enter salary:";
	std::cin >> salary;
	rewind(stdin);

	int amount_of_articles;
	std::cout << "Enter amount of articles:";
	std::cin >> amount_of_articles;
	rewind(stdin);

	try
	{
		student_teacher.set_first_name(first_name);
		student_teacher.set_last_name(last_name);
		student_teacher.set_marks(marks);
		student_teacher.set_scholarship(scholarship);
		student_teacher.set_rate(rate);
		student_teacher.set_salary(salary);
		student_teacher.set_amount_of_articles(amount_of_articles);
	}
	catch (std::string error_message)
	{
		std::cout << std::endl << error_message << std::endl;
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