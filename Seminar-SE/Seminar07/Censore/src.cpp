#include <iostream>
#include "Censore.h"

int main()
{
    Censore c([](char ch) -> bool { return ch >= 'a' && ch <= 'z'; }, std::cout);
    c << "Hello" << ", WorLd";
}