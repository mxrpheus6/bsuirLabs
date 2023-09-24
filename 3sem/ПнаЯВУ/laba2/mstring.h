#pragma once
#include <iostream>

class Mstring {
private:
	char* data;
	int len;
public:
	Mstring();
	Mstring(const char* ptr);
	Mstring(Mstring& m_str);
	Mstring& operator = (const Mstring& temp);
	Mstring& operator = (const char* temp);
	Mstring operator + (const Mstring& temp);
	Mstring operator + (const char* temp);
	~Mstring();
};