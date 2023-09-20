#include <iostream>

#include "square.h"

int main(void) {
	Square square;
	double input;

	std::cout << "Enter length of the square side:";
	while (!(std::cin >> input) || std::cin.peek() != '\n' || square.setLength(input) == false) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout<< "Invalid error. You must enter real number that more than zero\n"<< "Enter length of the square side:";
	}

	square.setPerimeter();
	square.setSquare();

	std::cout<<"Perrimeter = "<< square.getPerimeter()<< '\n';
	std::cout<<"Square = "<< square.getSquare();
	return 0;
}