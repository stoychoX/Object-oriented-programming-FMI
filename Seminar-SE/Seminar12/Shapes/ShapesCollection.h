#pragma once
#include "Shape.h"
#include <cstddef>

class ShapesCollection
{
private:
    Shape** data;
    size_t size;
    size_t capacity;

    void resize(size_t newCap);
    void copyFrom(const ShapesCollection&);
    void move(ShapesCollection&&);
    void free();

    void add(Shape*);
public:
    ShapesCollection();

    ShapesCollection(const ShapesCollection&);
    ShapesCollection(ShapesCollection&&) noexcept;

    ShapesCollection& operator=(const ShapesCollection&);
    ShapesCollection& operator=(ShapesCollection&&) noexcept;

    void addTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
    void addRectangle(int x1, int y1, int x3, int y3);
    void addCircle(int x, int y, double radius);

    void printAreas() const;

    ~ShapesCollection();
};