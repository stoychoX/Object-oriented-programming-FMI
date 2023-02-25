#include <iostream>
const double EPSILON = 0.00000001;
struct Point {
	double x;
	double y;
};
void readPoint(Point& point) {
	std::cin >> point.x;
	std::cin >> point.y;
}
void printPoint(const Point& point) {
	std::cout << point.x;
	std::cout << point.y;
}
double findDistToCenter(const Point& p) {
	return sqrt(p.x * p.x + p.y * p.y);
}
double findDistBetweenPoints(const Point& p1, const Point& p2) {
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
	return sqrt(dx * dx + dy * dy);
}
int findQuadrant(const Point& p) {
	if (p.x > 0 && p.y > 0) {
		return 1;
	}
	if (p.x > 0 && p.y < 0) {
		return 4;
	}
	if (p.x < 0 && p.y > 0) {
		return 2;
	}
	if (p.x < 0 && p.y < 0) {
		return 3;
	}
	return 0;
}
double myAbs(double num) {
	if (num < 0) {
		return num * (-1);
	}
	return num;
}
void findPointRelCircle(double radius, const Point& p) {
	double distOfPoint = findDistToCenter(p);
	if (distOfPoint < radius) {
		std::cout << "Point is in the circle"
			      << std::endl;
	}
	if (myAbs(distOfPoint - radius) < EPSILON) {
		std::cout << "Point is on the contour of the circle"
			      << std::endl;
	}
}
int main() {
	Point p1 = {-1.5, -1.5};
	Point p2 = { 3.14, 6.71 };
	std::cout << findDistToCenter(p1) << std::endl;
	std::cout << findDistBetweenPoints(p1, p2) << std::endl;
	std::cout << findQuadrant(p1) << std::endl;
	findPointRelCircle(3.0, p1);
}