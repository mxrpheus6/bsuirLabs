#include <iostream>
#include <cstring>

class Exception {
private:
	int code;
	char message[80];
public:
	Exception();
	Exception(int error_code, const char* error_message);
	void show() const;
};

class IntException : public Exception {
public:
	IntException(const char* error_message);
};

class DoubleException : public Exception {
public:
	DoubleException(const char* error_message);
};

class CharArrayException : public Exception {
public:
	CharArrayException(const char* error_message);
};

class IntArrayException : public Exception {
public:
	IntArrayException(const char* error_message);
};