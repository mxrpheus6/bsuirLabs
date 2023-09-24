#include "square.h"

Square::Square() {
	length = 0.0;
	square = 0.0;
	perimeter = 0.0;
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