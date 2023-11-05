#include <iostream>

#include "square.h"
#include "menu.h"
#include "mstring.h"

int main(void) {
	Square square;
	
	int choose = 0;
	int value = 0;

	while (choose != EXIT) {
		system("cls");
		print_menu();
		choose = input_check();
		rewind(stdin);

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
			case TEST_OPERATORS:
			{
				Square s1(2);
				Square s2(3);
				Square s3 = s1 + s2;
				std::cout << "s1 + s2 = " << s3.getSquare() << std::endl;
				double triangleLen = s1 & s2;
				std::cout << "s1 & s2 = " << triangleLen << std::endl;
				press_to_continue();
				break;
			}
			case TEST_STRINGS:
			{
				Mstring s1("abcdefgh");
				Mstring s2 = "test";
				Mstring s3 = s1;

				bool f1 = s2 == s3;
				bool f2 = s1 == "abcdefgh";
				bool f3 = s1 != s2;
				bool f4 = s1 != "Aboltus";

				std::cout << s1 << std::endl;
				std::cout << s2 << std::endl;
				std::cout << s3 << std::endl;
				std::cout << f1 << std::endl;
				std::cout << f2 << std::endl;
				std::cout << f3 << std::endl;
				std::cout << f4 << std::endl;

				s3 = s1(0, 3);
				std::cout << s3 << std::endl;
				std::cout << s3[0] << std::endl;
				Mstring s5;
				std::cin >> s5;
				s5 += s1;
				std::cout << s5 << std::endl;
				press_to_continue();
				break;
			}
			case EXIT:
				break;
			default:
				break;
		}

	}
	return 0;
}