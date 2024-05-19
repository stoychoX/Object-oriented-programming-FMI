#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

const double PI = 3.1415;
Circle::Circle(int x, int y, double radius) : Shape(1), radius(radius)
{
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}
double Circle::getPer() const
{
	return 2 * PI * radius;
}
bool Circle::isPointIn(int x, int y) const
{
	Shape::point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

bool Circle::isIntersectedWith(Shape* shape)
{
	return shape->isIntersectedWith(this);
}

bool Circle::isIntersectedWithRectange(Rectangle* shape)
{
	std::cout << "Circle + Rectangle" << std::endl;
	return true;
}

bool Circle::isIntersectedWithTriangle(Triangle* shape)
{
	std::cout << "Circle + Triangle" << std::endl;
	return true;
}

bool Circle::isIntersectedWithCircle(Circle* shape)
{
	std::cout << "Circle + Circle" << std::endl;
	return true;
}