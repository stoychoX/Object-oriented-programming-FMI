#include <iostream>
#include "String.h"

int main()
{
    String str = "Hello";
    std::cout << str.c_str() << std::endl;

    str.concat(", world!");
    std::cout << str.c_str();
}