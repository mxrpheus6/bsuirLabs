#include "square.h"

Square::Square() {
	length = 0.0;
	square = 0.0;
	perimeter = 0.0;
}

Square::Square(double length) {
	this->length = length;
	this->setPerimeter();
	this->setSquare();
}

double Square::getLength() {
	return length;
}

void Square::setLength(double length) {
	if (length <= 0.0) {
		throw std::string("Length should be more than zero");
	}
	this->length = length;
}

double Square::getSquare() {
	return square;
}

void Square::setSquare() {
	square = length * length;
}

double Square::getPerimeter() {
	return perimeter;
}

void Square::setPerimeter() {
	perimeter = length * 4;
}

Square Square::operator+(const Square obj) {
	Square result;
	result.setLength(this->length + obj.length);
	result.setSquare();
	result.setPerimeter();
	return result;
}

double Square::operator&(const Square obj) {
	double s = square + obj.square;
	double a = sqrt(4 * s / sqrt(3));
	return a;
}