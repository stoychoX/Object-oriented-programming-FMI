#include <iostream>
 
int Copying(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int ByPointer(int* a, int* b)
{
    if ((*a) < (*b))
        return (*a);
    return (*b);
}

int ByReference(const int& a,const int& b)
{
    if (a < b)
        return a;
    return b;   
}

int main()
{
    int a = 0, b = 0;
    std::cin >> a >> b;
    int* a1 = new int(a);
    int* a2 = new int(b);
    std::cout << ByPointer(&a, &b);
    std::cout << ByPointer(a1, a2);
    delete a1;
    delete a2;

}
