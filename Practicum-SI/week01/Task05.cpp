#include <iostream>

struct Point {
	double X = 0;
	double Y = 0;
};

Point getPoint()
{
	Point point;
	std::cin >> point.X;
	std::cin >> point.Y;
	return point;
}

void printPoint(const Point& point)
{
	std::cout << "(" << point.X << ", " << point.Y << ")" << std::endl;
}


double getDistanceBtwPoints(const Point& pointFrom, const Point& pointTo)
{
	double diffX = pointFrom.X - pointTo.X;
	double diffY = pointFrom.Y - pointTo.Y;
	return sqrt(diffX * diffX + diffY * diffY);
}

const Point center{0,0};
double getDistanceToCenter(const Point& point)
{
	return getDistanceBtwPoints(center, point);
}

int getQuadrant(const Point& point)
{
	if (point.X == 0 && point.Y == 0)
	{
		return 0;
	}
	if (point.X > 0)
	{
		if (point.Y > 0)
		{
			return 1;
		}
		else
		{
			return 4;
		}
	}
	else
	{
		if (point.Y > 0)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
}

void isPointLyingInsideOfCircle(const double& radius, const Point& K)
{
	const double epsilon = 0.0000001;
	const Point circleCenter{ 0.0, 0.0 };
	double dist = getDistanceBtwPoints(circleCenter, K);
	if (radius - dist >= 0)
	{
		if (radius - dist > epsilon)
		{
			std::cout << "inside";
		}
		else
		{
			std::cout << "on circle";
		}
	}
	else
	{
		std::cout << "out of circle";
	}
}

int main()
{
	Point a = getPoint();
	Point b = getPoint();
	std::cout << getDistanceBtwPoints(a, b) << std::endl;
	isPointLyingInsideOfCircle(1.9, a);
}
