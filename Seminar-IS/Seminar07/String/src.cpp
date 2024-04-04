#include "String.h"
#include <iostream>

int main()
{
    String str = "Hello";
    std::cout << str << std::endl;

    str += ", world!";
    std::cout << str << std::endl << str.length();

    std::cout << " " << str[10];
    str[10] = 'a';    
    std::cout << " " << str[10];
}