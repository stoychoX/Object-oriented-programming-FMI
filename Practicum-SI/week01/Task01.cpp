#include <iostream>

int f1(int a, int b)
{
    return a < b ? a : b;
}

int f2(const int& a, const int& b)
{
    return a < b ? a : b;
}

int f3(int* a, int* b)
{
    if (a != nullptr && b != nullptr)
    {
        return *a < *b ? *a : *b;
    }
}
int main()
{
    int a = 2, b = 4;
    std :: cout << f1(a, b)<<std::endl;
    std :: cout << f2(a, b) << std::endl;
    std :: cout << f3(&a, &b) << std::endl;
}

