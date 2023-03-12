#include <iostream>

struct Point
{
    int x;
    int y;
};

void ReadPoint(Point& pt)
{
    std::cin >> pt.x >> pt.y;
}

void PrintPoint(const Point& pt)
{
    std::cout << "( " << pt.x << " , " << pt.y << " )" << std::endl;
}

double FindingLenghtFromCenter(const Point& pt)
{
    return sqrt(pt.x * pt.x + pt.y * pt.y);
}

double FindingLenghtBetweenTwoPoint(const Point& pOne, const Point& pTwo)
{
    return sqrt((pOne.x - pTwo.x) * (pOne.x - pTwo.x) + (pOne.y - pTwo.y) * (pOne.y - pTwo.y));
}

int FindQuadrant(const Point& pt)
{
    if (pt.x > 0 && pt.y > 0)
        return 1;
    if (pt.x < 0 && pt.y > 0)
        return 2;
    if (pt.x < 0 && pt.y < 0)
        return 3;
    if (pt.x > 0 && pt.y < 0)
        return 4;
    return -1;
}

void PrintQuadrant(const Point& pt)
{
    switch (FindQuadrant(pt))
    {
    case 1:
        std::cout << "First Quadrant!";
        break;
    case 2:
        std::cout << "Second Quadrant!";
        break;
    case 3:
        std::cout << "Third Quadrant!";
        break;
    case 4:
        std::cout << "Fourth Quadrant!";
        break;
    default:
        std::cout << "Point is on the axis";
        break;
    }
}

bool IsItInCircle(const Point& pt, int r)
{   
    return pt.x * pt.x + pt.y * pt.y < r * r;
}

bool IsItOnCircle(const Point& pt, int r)
{
    return pt.x * pt.x + pt.y * pt.y == r* r;
}

void PrintWhereIsPointFromCircle(const Point& pt, int r)
{
    if (IsItInCircle(pt, r))
    {
        std::cout << "Point is in Circle!" << std::endl;
    }
    else if (IsItOnCircle(pt, r))
    {
        std::cout << "Point is on Circle Border!" << std::endl;
    }
    else
    {
        std::cout << "Point is not in Circle!" << std::endl;
    }
}

int main()
{
    Point pt1;
    Point pt2;
    int r = 0;
    ReadPoint(pt1);
    std::cin >> r;
    PrintWhereIsPointFromCircle(pt1, r);  
}
