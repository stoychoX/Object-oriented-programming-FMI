#include <iostream>
#include "UniquePtr.h"

int main()
{
    UniquePtr ptr(new A{1, 2});
    std::cout << ptr->x << " " << (*ptr).y << std::endl;

    ptr.reset(new A{2, 3});
    std::cout << ptr->x << " " << (*ptr).y << std::endl;

    A* raw = ptr.release();
    std::cout << raw->x << " " << raw->y;
}