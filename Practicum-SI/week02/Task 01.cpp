#include <iostream>
#include <fstream>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    std::ofstream myFileWrite("results.txt",std::ios::trunc);
    if (!myFileWrite.is_open())
    {
        return -1;
    }

    myFileWrite << a + b + c << '\n' << a * b * c;

    myFileWrite.close();

    std::ifstream myFileRead("results.txt");


    if (!myFileRead.is_open())
    {
        return -1;
    }

    int res1, res2;
    myFileRead >> res1;
    myFileRead.ignore();
    myFileRead >> res2;

    std::cout << res1 - res2;


}