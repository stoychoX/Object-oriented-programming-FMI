#include <iostream>
#include "Complex.h"

int main()
{
    Complex c(1, 4);;
    Complex c1(4, 5);

    std::cout << c << c1;

    c += c1;
    std::cout << c;
    c *= c1;
    std::cout << c;
    c /= c1;
    std::cout << c;
}