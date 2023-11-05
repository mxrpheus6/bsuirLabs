#pragma once
#include <iostream>
#include <string>

class Mstring {
private:
	char* data;
	int len;
public:
	Mstring();
	Mstring(const unsigned len);
	Mstring(const char* ptr);
	Mstring(Mstring& m_str);
	~Mstring();

	Mstring& operator = (const Mstring& temp);
	Mstring& operator = (const char* temp);
	Mstring operator + (const Mstring& temp);
	Mstring operator + (const char* temp);
	Mstring& operator+=(const Mstring& temp);
	Mstring& operator+=(const char* temp);

	bool operator == (const Mstring& temp);
	bool operator == (const char* temp);
	bool operator != (const Mstring& temp);
	bool operator != (const char* temp);

	char& operator [] (const unsigned index);
	Mstring operator () (const unsigned first_bound, const unsigned second_bound);
	friend std::ostream& operator<<(std::ostream& buff, Mstring& string);
	friend std::istream& operator >> (std::istream& input_buff, Mstring& string);

	int length();
};