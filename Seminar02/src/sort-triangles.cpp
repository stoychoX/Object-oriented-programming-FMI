#include <iostream>
#include <cmath>

struct Point
{
    double x;
    double y;
};

void readPoint(Point& p)
{
    std::cin >> p.x >> p.y;
}

void printPoint(const Point& p)
{
    std::cout << p.x << " " << p.y << std::endl;
}

double findDistance(const Point& p1, const Point& p2)
{
    double dx = (p1.x - p2.x);
    double dy = (p1.y - p2.y);
    return sqrt(dx * dx + dy * dy);
}

struct Triangle
{
    Point p1;
    Point p2;
    Point p3;
};

void readTriangle(Triangle& t)
{
    readPoint(t.p1);
    readPoint(t.p2);
    readPoint(t.p3);
}

void printTriangle(const Triangle& t)
{
    printPoint(t.p1);
    printPoint(t.p2);
    printPoint(t.p3);
    std::cout << std::endl;
}

double findArea(const Triangle& t)
{
    double sideA = findDistance(t.p1, t.p2);
    double sideB = findDistance(t.p1, t.p3);
    double sideC = findDistance(t.p2, t.p3);

    double p = (sideA + sideB + sideC) / 2;

    return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
}

void sortTriangles(Triangle* triangles, unsigned n)
{
    double* faces = new double[n];

    for (size_t i = 0; i < n; i++)
    {
        faces[i] = findArea(triangles[i]);
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        size_t minElementIndex = i;

        for (size_t j = i + 1; j < n; j++)
        {
            if (faces[j] < faces[minElementIndex])
            {
                minElementIndex = j;
            }
        }

        if (minElementIndex != i)
        {
            std::swap(triangles[minElementIndex], triangles[i]);
            std::swap(faces[minElementIndex], faces[i]);
        }
    }

    delete[] faces;
}

int main()
{
    // 1. Read triangles

    // Number of triangles
    unsigned n = 0;
    std::cin >> n;

    // Create array of n triangles.
    Triangle* triangles = new Triangle[n];

    for (size_t i = 0; i < n; i++)
    {
        readTriangle(triangles[i]);
    }

    // 2. Sort triangles.
    sortTriangles(triangles, n);

    // 3. Print triangles.
    for (size_t i = 0; i < n; i++)
    {
        printTriangle(triangles[i]);
    }

    delete[] triangles;
}