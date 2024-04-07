#include "String.h"
#include <iostream>

int main()
{
    String str = "Hello";
    std::cout << str;
    String str2;
    std::cin >> str2;
    std::cout << std::endl << str2 << std::endl;
    str += str2;
    std::cout << str;
}