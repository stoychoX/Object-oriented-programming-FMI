#pragma once

// We promice to each .cpp file in which we include
// lib.h two void functions (f and g) and class Entity.

// What do they do? We define this in the lib.cpp file!

void f();
void g();

class Entity
{
private:
    int _x;
public:
    Entity(int x);
    int get() const;
};