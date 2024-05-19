#include "ShapesCollection.h"
#include<iostream>
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

ShapesCollection::ShapesCollection() :
    data(nullptr),
    size(0),
    capacity(8)
{
    data = new Shape*[capacity] {};
}

void ShapesCollection::free()
{
    for (size_t i = 0; i < size; i++)
        delete data[i];

    delete[] data;    
}

void ShapesCollection::add(Shape* s)
{
    if(size == capacity)
        resize(capacity * 2);
    data[size++] = s;
}

void ShapesCollection::move(ShapesCollection&& other)
{
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = other.capacity = 0;
}

void ShapesCollection::resize(size_t newCap)
{
    if(capacity <= newCap)
        return;
    
    Shape** newData = new Shape*[newCap]{};

    for (size_t i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}

ShapesCollection& ShapesCollection::operator=(const ShapesCollection& other)
{
    if(this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

ShapesCollection& ShapesCollection::operator=(ShapesCollection&& other) noexcept
{
    if(this != &other)
    {
        free();
        move(std::move(other));
    }
    return *this;
}

ShapesCollection::~ShapesCollection()
{
    free();
}

void ShapesCollection::addTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    add(new Triangle(x1, y1, x2, y2, x3, y3));
}
void ShapesCollection::addRectangle(int x1, int y1, int x3, int y3)
{
    add(new Rectangle(x1, y1, x3, y3));
}

void ShapesCollection::addCircle(int x, int y, double radius)
{
    add(new Circle(x, y, radius));
}

void ShapesCollection::copyFrom(const ShapesCollection& other)
{
    size = other.size;
    capacity = other.capacity;

    // I want to copy all the data from other to *this
    data = new Shape*[capacity]{};
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i]->clone();
    }
}

void ShapesCollection::printAreas() const
{
    for (size_t i = 0; i < size; i++)
        std::cout << data[i]->getArea() << " ";
}


ShapesCollection::ShapesCollection(const ShapesCollection& other)
{
    copyFrom(other);
}

ShapesCollection::ShapesCollection(ShapesCollection&& other) noexcept
{
    move(std::move(other));
}