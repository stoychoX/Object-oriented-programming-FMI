#include <iostream>
#include <fstream>

void writeInResultFile(const char* fileName, int sum, int product)
{
    std::ofstream myFile(fileName, std::ios::trunc);
    if (!myFile.is_open())
        return;

    myFile << sum << ' ' << product;

    myFile.close();
}
void GetDiff(const char* fileName)
{
    std::ifstream myFile(fileName);
    if (!myFile.is_open())
        return;

    int sum, product;
    myFile >> sum;
    myFile.ignore();
    myFile >> product;

    myFile.close();

    std::cout << sum - product;

}

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    int sum = a + b + c;
    int product = a * b * c;

    writeInResultFile("result.txt", sum, product);
    GetDiff("result.txt");
}
