#include <bits/stdc++.h>
using namespace std;

/*
Given a 2-D plane, there are many rectangles(whose edges are parallel to X and Y axis) 
and there are many infinite lines(vertical and horizontal). 
The ask was to find total number of intersection points of the lines with the rectangles.

*/

// Asssumption - 1. no overlapping of lines with the rectangle boundaries
//				 2. Plane only consists of rectangles and lines and no need to worry about other shapes

// class -> Plane has {Rectangle, Line}
//		-> addRectangle, addLine, removeRectangle, removeLine
//		-> getAllIntersectionPoints
// Rectangle 
	// topLeftX, topLeftY
	// bottomRightX, bottomRightY
	
// Line
	// x, y
	// isHorizontalInfinite
	// isVerticalInfinite

class Line {
private:
	double x;
	double y;
	bool isVerticalInfinite;
public:
	Line(double x, double y, bool isVerticalInfinite): x(x), y(y), isVerticalInfinite(isVerticalInfinite){}
	bool isVertical()
	{
		return(isVerticalInfinite);	
	}
	double getX()
	{
		return(x);
	}
	double getY()
	{
		return(y);
	}
};

class Rectangle {
private:
	double bottomLeftX;
	double bottomLeftY;
	double topRightX;
	double topRightY;
	
public:
	Rectangle(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY) : bottomLeftX(bottomLeftX), bottomLeftY(bottomLeftY), topRightX(topRightX), topRightY(topRightY) {}
	double getbottomLeftX() 
	{
		return(bottomLeftX);
	}
	double getbottomLeftY()
	{
		return(bottomLeftY);
	}
	double gettopRightX()
	{
		return(topRightX);
	}
	double gettopRightY()
	{
		return(topRightY);
	}
};

class Plane{
private:
	vector<Rectangle*> rectangles;
	vector<Line*> lines;
public:
	Plane(){}
	void addRectangle(Rectangle *rectangle) 
	{ 
		rectangles.push_back(rectangle);
	}
	void removeRectangle(Rectangle *rectangle)
	{
		int index = 0;
		for(auto currentRectangle: rectangles)
		{
			if (currentRectangle == rectangle)
			{
				break;
			}
			index += 1;
		}
		rectangles.erase(rectangles.begin()+index);
	}
	void addLine(Line *line) 
	{ 
		lines.push_back(line);
	}
	void removeLine(Line *line)
	{
		int index = 0;
		for(auto currentLine: lines)
		{
			if (currentLine == line)
			{
				break;
			}
			index += 1;
		}
		lines.erase(lines.begin()+index);
	}
	int getIntersectionPoints()
	{
		int intersectionCount = 0;
		for (auto rectangle: rectangles)
		{
			for (auto line: lines)
			{
				if (line->isVertical())
				{
					if (rectangle->getbottomLeftX() <= line->getX() && rectangle->gettopRightX() >= line->getX())
						intersectionCount += 2;
				}
				else
				{
					if (rectangle->getbottomLeftY() <= line->getY() && rectangle->gettopRightY() >= line->getY())
						intersectionCount += 2;
				}
			}
		}
		cout<<"result = "<<intersectionCount<<endl;
		return(intersectionCount);
	}
};
int main() {
	Line *line1 = new Line(2, 0, true);
	Line *line2 = new Line(5, 0, true);
	Line *line3 = new Line(9, 0, true);
	
	Line *line4 = new Line(0, 1, false);
	Line *line5 = new Line(0, 2, false);
	Line *line6 = new Line(0, 4, false);
	Line *line7 = new Line(0, 19, false);
	
	Rectangle *rect1 = new Rectangle(1,3,3,6);
	
	Plane plane;
	plane.addRectangle(rect1);
	
	plane.getIntersectionPoints();
	
	plane.addLine(line1);
	plane.addLine(line2);
	plane.addLine(line3);
	plane.addLine(line4);
	plane.addLine(line5);
	plane.addLine(line6);
	plane.addLine(line7);
	
	plane.getIntersectionPoints();
	return 0;
}