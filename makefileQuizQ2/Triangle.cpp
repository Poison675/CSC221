/*
 * Triangle.cpp
 *
 *  Created on: Sep 9, 2021
 *      Author: Luper
 */


#include "Triangle.h"

Triangle::Triangle(Point alpha, Point beta, Point charlie)
{
	a = alpha;
	b = beta;
	c = charlie;
}

const Point& Triangle::getA() const { return a; }
void Triangle::setA(const Point& a) { this->a = a; }
const Point& Triangle::getB() const { return b; }
void Triangle::setB(const Point& b) { this->b = b; }
const Point& Triangle::getC() const { return c; }
void Triangle::setC(const Point& c) { this->c = c; }

/*
Triangle::Triangle(Point alpha, Point beta, Point charlie)
{
	a = alpha;
	b = beta;
	c = charlie;
}


const Point& Triangle::getA() const { return a; }
void Triangle::setA(const Point& a) { this->a = a; }
const Point& Triangle::getB() const { return b; }
void Triangle::setB(const Point& b) { this->b = b; }
const Point& Triangle::getC() const { return c; }
void Triangle::setC(const Point& c) { this->c = c; }
 */



