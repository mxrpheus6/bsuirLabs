#include <iostream>

int input_check() {
	int input;
	while (!(std::cin >> input) || std::cin.peek() != '\n') {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Invalid error. You must enter integer number." << std::endl;
	}
	return input;
}

void press_to_continue() {
	std::cout << "Press enter to continue...";
	std::cin.ignore();
	std::cin.get();
}

void print_menu()
{
	std::cout << "MENU" << std::endl
		<< "1) - Push" << std::endl
		<< "2) - Pop" << std::endl
		<< "3) - Print" << std::endl
		<< "4) - Size" << std::endl
		<< "5) - Front" << std::endl
		<< "6) - Rear" << std::endl
		<< "7) - Exit" << std::endl
		<< "Your choose: ";
}