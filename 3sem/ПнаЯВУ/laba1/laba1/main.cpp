#include <iostream>

#include "square.h"

int main(void) {
	Square square;
	double input;
	while (true) {
		std::cout<<"Enter length of the square:";
		std::cin>>input;
		square.setLength(input);
		if (square.getLength() != 0.0) {
			break;
		}
		std::cout << "Invalid length. Try again.";
	}
	square.setLength(input);
	square.setPerimeter();
	square.setSquare();
	std::cout << square.getPerimeter()<<'\n';
	std::cout << square.getSquare();
	return 0;
}