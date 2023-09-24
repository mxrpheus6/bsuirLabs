#include "mstring.h"

Mstring::Mstring() {
	this->data = nullptr;
	this->len = 0;
}

Mstring::Mstring(const char* ptr) {
	len = strlen(ptr);
	data = new char[len + 1];

	for (int i = 0; i < len; i++) {
		data[i] = ptr[i];
	}
}

Mstring::Mstring(Mstring& m_str) {
	len = m_str.len;
	data = new char[len + 1];

	for (int i = 0; i < len; i++) {
		data[i] = m_str.data[i];
	}
}

Mstring& Mstring::operator = (const Mstring& temp) {
	if (this == &temp) {
		return *this;
	}

	delete[] this->data;
	len = temp.len;
	data = new char[len + 1];

	for (int i = 0; i < len; i++) {
		data[i] = temp.data[i];
	}

	return *this;
}

Mstring& Mstring::operator = (const char* temp) {
	delete[] this->data;
	len = strlen(temp);
	data = new char[len + 1];

	for (int i = 0; i < len; i++) {
		data[i] = temp[i];
	}
	
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
		result[i] = temp[i];
	}

	for (j = 0; i < len + strlen(temp); j++, i++) {
		result[i] = temp[j];
	}

	result[i] = '\0';

	Mstring string(result);

	return string;
}

Mstring::~Mstring() {
	delete[] this->data;
}