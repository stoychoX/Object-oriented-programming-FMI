#include <iostream>

int first(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else return b;
}

int second(int* a, int* b)
{
    if (a < b)
    {
        return *a;
    }
    else return *b;
}

int third(int& a, int& b)
{
    if (a < b)
    {
        return a;
    }
    else return b;
}

int main()
{
    int a = 3;
    int b = 5;
    int* a1 = &a;
    int* b1 = &b;
    int& a2 = a;
    int& b2 = b;

    std::cout << first(a,b)<<std::endl;
    std::cout << second(a1, b1) << std::endl;
    std::cout << third(a2,b2) << std::endl;
}