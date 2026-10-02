//============================================================================
// Name        : Makefile.cpp
// Author      : Shawn
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Point.h"

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	Point temp(23, 24);

	cout << temp.getXCoordinate() << endl;
	cout << temp.getYCoordinate() << endl;




	return 0;
}
