#include <iostream>
#include <fstream>

void writeInFile(int num1, int num2, int num3)
{
    std::ofstream outputStream("result.txt");
    if (!outputStream.is_open())
    {
        std::cout << "Error while opening the file";
        return;
    }

    outputStream << num1 + num2 + num3 << std::endl
                 << num1 * num2 * num3 << std::endl;

    outputStream.close();
}

void readFromFile()
{
    std::ifstream inputStream("result.txt");
    if (!inputStream.is_open())
    {
        std::cout << "Error while opening the file";
        return;
    }
    int first, second;
    inputStream >> first;
    inputStream.ignore();
    inputStream >> second;

    std::cout << first - second;
    inputStream.close();
}
int main()
{
    int num1, num2, num3;
    std::cin >> num1 >> num2 >> num3;
    writeInFile(num1, num2, num3);
    readFromFile();
    return 0;
}
