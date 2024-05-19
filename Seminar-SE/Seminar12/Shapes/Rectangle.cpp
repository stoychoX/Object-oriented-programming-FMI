#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4)
{
	setPoint(0, x1, y1);
	setPoint(1, x1, y3);
	setPoint(2, x3, y3);
	setPoint(3, x3, y1);
}
double Rectangle::getArea() const
{
	const Shape::point& p0 = getPointAtIndex(0);
	const Shape::point& p1 = getPointAtIndex(1);
	const Shape::point& p3 = getPointAtIndex(3);

	return p0.getDist(p1) * p0.getDist(p3);
}

bool Rectangle::isPointIn(int x, int y) const
{
	Shape::point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).x &&
		p.y <= getPointAtIndex(0).y && p.y >= getPointAtIndex(2).y;
}

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

bool Rectangle::isIntersectedWith(Shape* shape)
{
	return shape->isIntersectedWithRectange(this);
}

bool Rectangle::isIntersectedWithRectange(Rectangle* shape)
{
	std::cout << "Rectangle + Rectangle" << std::endl;
	return true;
}

bool Rectangle::isIntersectedWithTriangle(Triangle* shape)
{
	std::cout << "Rectangle + Triangle" << std::endl;
	return true;
}

bool Rectangle::isIntersectedWithCircle(Circle* shape)
{
	std::cout << "Rectangle + Circle" << std::endl;
	return true;
}