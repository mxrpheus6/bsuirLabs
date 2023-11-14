#include "exceptions.h"

Exception::Exception() {
	code = 0;
	message[0] = '\0';
}

Exception::Exception(int error_code, const char* error_message) {
	code = error_code;
	strcpy_s(this->message, error_message);
}

void Exception::show() const {
	std::cout << "\nError code: " << code << "\nMessage: " << message << std::endl;
}

IntException::IntException(const char* error_message) : Exception(1, error_message) {}
DoubleException::DoubleException(const char* error_message) : Exception(2, error_message) {}
CharArrayException::CharArrayException(const char* error_message) : Exception(3, error_message) {}
IntArrayException::IntArrayException(const char* error_message) : Exception(4, error_message) {}