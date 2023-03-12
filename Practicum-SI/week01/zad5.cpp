#include <iostream>

struct Point {
	double x;
	double y;
};

void enterPoint(Point& p) {
	std::cin >> p.x;
	std::cin >> p.y;
}

void printPoint(const Point& p) {
	std::cout << "x: " << p.x << std::endl;
	std::cout << "y: " << p.y << std::endl;
}

double distanceFromCenter(const Point& p) {
	return sqrt(p.x * p.x + p.y * p.y);
}

double distance(const Point& p1, const Point& p2) {
	double dy = p2.y - p1.y;
	double dx = p2.x - p1.y;
	return sqrt(dx * dx + dy * dy);
}

enum class quadrant {
	first,
	second,
	third,
	fourth,
	center,
	x_axis,
	y_axis
};

quadrant findQuadrant(const Point& p) {
	if (p.x < 0) {
		if (p.y < 0) {
			return quadrant::third;
		}
		if (p.y == 0) {
			return quadrant::x_axis;
		}
		if (p.y > 0) {
			return quadrant::second;
		}
	}
	if (p.x == 0) {
		if (p.y < 0) {
			return quadrant::y_axis;
		}
		if (p.y == 0) {
			return quadrant::center;
		}
		if (p.y > 0) {
			return quadrant::y_axis;
		}
	}
	if (p.x > 0) {
		if (p.y < 0) {
			return quadrant::fourth;
		}
		if (p.y == 0) {
			return quadrant::x_axis;
		}
		if (p.y > 0) {
			return quadrant::first;
		}
	}
}

// 1 -> is inside   2 -> is on edge    3 -> is outside
int isInside(const Point& p, const double radius) {
	double distance = distanceFromCenter(p);
	if (distance - radius > -0.0000001 && distance - radius < 0.0000001) {
		return 2;
	}
	if (distance > radius) {
		return 3;
	}
	if (distance < radius) {
		return 1;
	}
}

int main() {
	Point p;
	enterPoint(p);
	printPoint(p);
	std::cout << distanceFromCenter(p) << std::endl;
	Point p1;
	enterPoint(p1);
	std::cout << distance(p, p1) << std::endl;
	switch (findQuadrant(p)) {
		case quadrant::first: std::cout << "1"; break;
		case quadrant::second: std::cout << "2"; break;
		case quadrant::third: std::cout << "3"; break;
		case quadrant::fourth: std::cout << "4"; break;
		case quadrant::center: std::cout << "5"; break;
		case quadrant::x_axis: std::cout << "6"; break;
		case quadrant::y_axis: std::cout << "7"; break;
	}
	std::cout << std::endl;

	std::cout << isInside(p, 5);
}