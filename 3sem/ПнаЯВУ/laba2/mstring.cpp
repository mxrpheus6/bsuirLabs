#include "mstring.h"

Mstring::Mstring() {
	data = nullptr;
	len = 0;
}

Mstring::Mstring(const unsigned len) {
	this->len = len;
	data = new char[len + 1];
}

Mstring::Mstring(const char* ptr) {
	len = strlen(ptr);
	data = new char[len + 1];
	int i;

	for (i = 0; i < len; i++) {
		data[i] = ptr[i];
	}

	data[i] = '\0';
}

Mstring::Mstring(Mstring& m_str) {
	len = m_str.len;
	data = new char[len + 1];
	int i;

	for (i = 0; i < len; i++) {
		data[i] = m_str.data[i];
	}

	data[i] = '\0';
}

Mstring::~Mstring() {
	delete[] this->data;
}

Mstring& Mstring::operator = (const Mstring& temp) {
	if (this == &temp) {
		return *this;
	}

	delete[] this->data;
	len = temp.len;
	data = new char[len + 1];

	int i;
	for (i = 0; i < len; i++) {
		data[i] = temp.data[i];
	}

	data[i] = '\0';

	return *this;
}

Mstring& Mstring::operator = (const char* temp) {
	delete[] this->data;
	len = strlen(temp);
	data = new char[len + 1];
	int i;

	for (i = 0; i < len; i++) {
		data[i] = temp[i];
	}
	
	data[i] = '\0';

	return *this;
}

Mstring Mstring::operator + (const Mstring& temp) {
	char* result = new char[len + temp.len + 1];
	int i, j;

	for (i = 0; i < len; i++) {
		result[i] = data[i];
	}

	for (j = 0; i < len + temp.len; j++, i++) {
		result[i] = temp.data[j];
	}

	result[i] = '\0';

	Mstring string(result);

	return string;
}

Mstring Mstring::operator + (const char* temp) {
	char* result = new char[len + strlen(temp) + 1];
	int i, j;

	for (i = 0; i < len; i++) {
		result[i] = data[i];
	}

	for (j = 0; i < len + strlen(temp); j++, i++) {
		result[i] = temp[j];
	}

	result[i] = '\0';

	Mstring string(result);

	return string;
}

Mstring& Mstring::operator += (const Mstring& temp) {
	*this = *this + temp;

	return *this;
}

Mstring& Mstring::operator += (const char* temp) {
	*this = *this + temp;

	return *this;
}

bool Mstring::operator == (const Mstring& temp) {
	if (len != temp.len)
		return false;

	for (int i = 0; i < len; i++) {
		if (data[i] != temp.data[i])
			return false;
	}

	return true;
}

bool Mstring::operator == (const char* temp) {
	if (len != strlen(temp))
		return false;

	for (int i = 0; i < len; i++) {
		if (data[i] != temp[i])
			return false;
	}

	return true;
}

bool Mstring::operator != (const Mstring& temp) {
	return !(*this == temp);
}

bool Mstring::operator != (const char* temp) {
	return !(*this == temp);
}

char& Mstring::operator [] (const unsigned index) {
	if (index >= len) {
		throw std::string("Index out of bound");
	}
	return data[index];
}

Mstring Mstring::operator () (const unsigned first_bound, const unsigned second_bound) {
	if (first_bound >= len || second_bound >= len || first_bound > second_bound) {
		throw std::string("Index out of bounds");
	}

	const unsigned new_len = second_bound - first_bound + 1;

	Mstring result(new_len + 1);

	int j = 0;
	for (int i = first_bound; i <= second_bound; i++, j++) {
		result[j] = data[i];
	}

	result[j] = '\0';

	return result;
}

std::ostream& operator << (std::ostream& output_buff, Mstring& string) {
	output_buff << string.data;
	return output_buff;
}

std::istream& operator >> (std::istream& input_buff, Mstring& string) {
	if (string.data != nullptr)
		delete[] string.data;

	std::string buff_string;
	//input_buff >> buff_string;
	std::getline(input_buff, buff_string);

	string.len = buff_string.length();
	string.data = new char[string.len + 1];

	int i;
	for (i = 0; i < string.len; i++)
		string.data[i] = buff_string[i];

	string.data[i] = '\0';

	return input_buff;
}

int Mstring::length() {
	return len;
}