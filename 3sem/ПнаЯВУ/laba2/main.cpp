#include <iostream>

#include "square.h"
#include "menu.h"

int main(void) {
	Square square;
	
	int choose = 0;
	int value = 0;

	while (choose != EXIT) {
		system("cls");
		print_menu();
		choose = input_check();

		switch (choose) {
			case SET:
				std::cout << "Enter length of the square side: ";
				value = input_check();

				try {
					square.setLength(value);
				}
				catch (std::string error_message) {
					std::cout << error_message << std::endl;
					break;
				}
				square.setSquare();
				square.setPerimeter();
				press_to_continue();
				break;
			case PRINT_AREA:
				std::cout << "Square = " << square.getSquare() << std::endl;
				press_to_continue();
				break;
			case PRINT_PERIMETER:
				std::cout << "Perimeter = " << square.getPerimeter() << std::endl;
				press_to_continue();
				break;
			case EXIT:
				break;
			default:
				break;
		}

	}
	return 0;
}