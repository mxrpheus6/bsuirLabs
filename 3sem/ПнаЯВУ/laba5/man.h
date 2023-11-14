#pragma once
#include <iostream>

#include "exceptions.h"

#define MAX_NAME_LENGTH 20

class Man {
private:
	char first_name[MAX_NAME_LENGTH];
	char last_name[MAX_NAME_LENGTH];
public:
	Man();
	Man(char* first_name, char* last_name);

	void set_first_name(const char* first_name);
	void set_last_name(const char* last_name);

	const char* get_fisrt_name() const;
	const char* get_last_name() const;

	void speak() const;
};