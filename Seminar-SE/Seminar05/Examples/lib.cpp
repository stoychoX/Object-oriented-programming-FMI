#include "lib.h"
#include <iostream> // iostream included in lib.cpp

void f()
{
    std::cout << "F";
}

void g()
{
    std::cout << "g";
}

Entity::Entity(int x) : _x(x) {}

int Entity::get() const
{
    return _x;
}