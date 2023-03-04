#include <iostream>

const double EPSILON = 1e-6;

enum class Quadant
{
    First = 1,
    Second = 2,
    Third = 3,
    Forth = 4
};

struct Point
{
    double x;
    double y;
};

void readPoint(Point &point)
{
    std::cin >> point.x;
    std::cin >> point.y;
}

void printPoint(const Point &point)
{
    std::cout << "Point is with coordinates: (" << point.x << ", " << point.y << ")";
}

size_t getDist(const Point &poin1, const Point &point2)
{
    int dx = poin1.x - point2.x;
    int dy = poin1.y - point2.y;
    return sqrt(dx * dx + dy * dy);
}

Quadant getLocation(const Point &point)
{

    if (point.x > 0 && point.y > 0)
    {
        return Quadant::First;
    }
    else if (point.x < 0 && point.y > 0)
    {
        return Quadant::Second;
    }
    else if (point.x < 0 && point.y < 0)
    {
        return Quadant::Third;
    }
    else
    {
        return Quadant::Forth;
    }
}

void checkCircle(const Point &pointK, double r)
{
    double distToPoint = sqrt(pointK.x * pointK.x + pointK.y * pointK.y);
    if (std::abs(distToPoint - r * r) < EPSILON)
    {
        std::cout << "Point K is on the outline of the circle";
    }
    else if (distToPoint < r * r)
    {
        std::cout << "Point K is inside the circle";
    }
}

int main()
{
    return 0;
}