//============================================================================
// Name        : Makefile.cpp
// Author      : Shawn
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Triangle.h"
#include "Point.h"
using namespace std;

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	Point temp(23, 24);

	cout << temp.getXCoordinate() << endl;
	cout << temp.getYCoordinate() << endl;

	Triangle test;
	test.setA(Point(23, 24));
	test.setB(Point(0, 0)),
	test.setC(Point(-23, 24));

	cout << test.getA().getXCoordinate() << endl;

	return 0;
}
