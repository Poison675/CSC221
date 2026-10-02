#ifndef POINT_H_
#define POINT_H_

class Point
{

public:

	Point(int xValue, int yValue) { xCoordinate=xValue; yCoordinate=yValue; }
	int getXCoordinate() const { return xCoordinate; }
	void setXCoordinate(int coordinate) { xCoordinate = coordinate; }
	int getYCoordinate() const { return yCoordinate; }
	void setYCoordinate(int coordinate) { yCoordinate = coordinate; }


private:
	int xCoordinate;
	int yCoordinate;

};

#endif


