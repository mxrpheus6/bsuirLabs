#include "man.h"

Man::Man() {
	this->first_name[0] = '\0';
	this->last_name[0] = '\0';
}

Man::Man(char* first_name, char* last_name) {
	set_first_name(first_name);

}

void Man::set_first_name(const char* first_name) {
	if (strlen(first_name) > MAX_NAME_LENGTH - 1) {
		throw CharArrayException("Length of the first name is more than permissible");
	}

	int i;
	for (i = 0; i < strlen(first_name); i++) {
		this->first_name[i] = first_name[i];
	}
	this->first_name[i] = '\0';
}

void Man::set_last_name(const char* last_name) {
	if (strlen(last_name) > MAX_NAME_LENGTH - 1) {
		throw CharArrayException("Length of the first name is more than permissible");
	}

	int i;
	for (i = 0; i < strlen(last_name); i++) {
		this->last_name[i] = last_name[i];
	}
	this->last_name[i] = '\0';
}

const char* Man::get_fisrt_name() const {
	return this->first_name;
}

const char* Man::get_last_name() const {
	return this->last_name;
}

void Man::speak() const {
	std::cout << first_name << " says: What's up!" << std::endl;
}