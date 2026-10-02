/*
 * Triangle.h
 *
 *  Created on: Sep 9, 2021
 *      Author: Luper
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Point.h"


class Triangle
{
public:
	Triangle() { }

	Triangle(Point alpha, Point beta, Point charlie);
	const Point& getA() const;
	void setA(const Point& a);
	const Point& getB() const;
	void setB(const Point& b);
	const Point& getC() const;
	void setC(const Point& c);

private:
	Point a;
	Point b;
	Point c;

};

#endif /* TRIANGLE_H_ */
