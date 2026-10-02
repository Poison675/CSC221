#ifndef POINT_H_
#define POINT_H_

class Point
{

public:
	Point() { xCoordinate=0; yCoordinate=0; }
	Point(int xValue, int yValue) { xCoordinate=xValue; yCoordinate=yValue; }
	int getXCoordinate() const { return xCoordinate; }
	void setXCoordinate(int coordinate) { xCoordinate = coordinate; }
	int getYCoordinate() const { return yCoordinate; }
	void setYCoordinate(int coordinate) { yCoordinate = coordinate; }

	const Point &operator = (const Point &source)
	{
		if(this == &source) // this is a self assignment checker
		{ return *this; }	// returns the pointer to the current object
		// otherwise copy

		//new-instance now = source instance
		this->xCoordinate = source.xCoordinate;
		this->yCoordinate = source.yCoordinate;

		return *this; // returns previously empty instance
	}


private:
	int xCoordinate;
	int yCoordinate;

};

#endif


