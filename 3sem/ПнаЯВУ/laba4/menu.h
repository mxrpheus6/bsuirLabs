#pragma once
#include <iostream>

#include "menu.h"
#include "queue.h"

enum Menu {
	PUSH = 1,
	POP,
	PRINT,
	SIZE,
	FRONT,
	REAR,
	EXIT
};

int input_check();
void press_to_continue();
void print_menu();

template<typename T>
void menu() {
	Queue<T> queue;

	T temp;
	int choose = -1;

	while (choose != EXIT) {
		system("cls");
		print_menu();
		choose = input_check();

		switch (choose) {
		case PUSH:
		{
			std::cout << "Enter data:";
			std::cin >> temp;
			queue.push(temp);
			press_to_continue();
			break;
		}
		case POP:
		{
			try {
				T temp = queue.pop();
				std::cout << "Popped data is " << temp << std::endl;
			}
			catch (std::string error_message) {
				std::cout << error_message << std::endl;
			}

			press_to_continue();
			break;
		}
		case PRINT:
		{
			try {
				queue.print();
			}
			catch (std::string error_message) {
				std::cout << error_message << std::endl;
			}

			press_to_continue();
			break;
		}
		case SIZE:
		{
			std::cout << "The size of queue is " << queue.size() << std::endl;
			press_to_continue();
			break;
		}
		case FRONT:
		{

			try {
				T temp = queue.front();
				std::cout << "Front data is " << temp << std::endl;
			}
			catch (std::string error_message) {
				std::cout << error_message << std::endl;
			}

			press_to_continue();
			break;
		}
		case REAR:
		{

			try {
				T temp = queue.rear();
				std::cout << "Rear data is " << temp << std::endl;
			}
			catch (std::string error_message) {
				std::cout << error_message << std::endl;
			}

			press_to_continue();
			break;
		}
		default:
		{
			break;
		}
		}
	}
}
