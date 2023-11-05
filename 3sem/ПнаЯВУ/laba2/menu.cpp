#include "menu.h"

void print_menu() {
	std::cout
		<< "MENU" << std::endl
		<< "1. Change length of the square side" << std::endl
		<< "2. Print square area" << std::endl
		<< "3. Print square perimeter" << std::endl
		<< "4. Test operators" << std::endl
		<< "5. Test strings" << std::endl
		<< "6. Exit" << std::endl
		<< "Your choice:";
}

int input_check() {
	double input;
	while (!(std::cin >> input) || std::cin.peek() != '\n') {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Invalid error. You must enter real number that more than zero" << std::endl;
	}
	return input;
}

void press_to_continue() {
	std::cout << "Press enter to continue...";
	std::cin.ignore();
	std::cin.get();
}