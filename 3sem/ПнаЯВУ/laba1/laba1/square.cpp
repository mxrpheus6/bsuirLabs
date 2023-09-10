#include "square.h"

Square::Square() {
	length = 0.0;
	square = 0.0;
	perimeter = 0.0;
}

double Square::getLength() {
	return length;
}

bool Square::setLength(double length) {
	if (length <= 0.0) {
		return false;
	}
	this->length = length;
	return true;
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