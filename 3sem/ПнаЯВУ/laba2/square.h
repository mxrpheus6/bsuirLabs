#pragma once

#include <iostream>
#include <iomanip>
#include <math.h>

class Square {
private:
	double length;
	double square;
	double perimeter;
public:
	Square();
	Square(double length);
	double getLength();
	void setLength(double length);
	double getSquare();
	void setSquare();
	double getPerimeter();
	void setPerimeter();
	Square operator+(const Square obj);
	double operator&(const Square obj);
};