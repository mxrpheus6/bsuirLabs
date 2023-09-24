#pragma once

#include <iostream>
#include <iomanip>

class Square {
private:
	double length;
	double square;
	double perimeter;
public:
	Square();
	double getLength();
	void setLength(double length);
	double getSquare();
	void setSquare();
	double getPerimeter();
	void setPerimeter();
};