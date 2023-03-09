#include <iostream>
#include <fstream>

struct Example
{
    int data;
    char buff[8];
};
void ReadFromConsole(Example& ex)
{
    std::cin >> ex.data;
    std::cin.ignore();
    std::cin.getline(ex.buff, sizeof(ex.buff));
}
void SaveToFile(const char* fileName, const Example* array, int n)
{
    std::ofstream of(fileName, std::ios::out |
        std::ios::app | std::ios::binary);
    if (!of.is_open())
    {
        std::cout << "Error!";
        return;
    }
    for (int i = 0; i < n; i++)
    {
        of.write((const char*)&array[i], sizeof(Example));
    }
    of.close();
}
int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore();
    Example* exArr = new Example[n];
    for (size_t i = 0; i < n; i++)
    {
        ReadFromConsole(exArr[i]);
    }
    char fileName[1024];
    std::cin.getline(fileName, 1024);
    SaveToFile(fileName, exArr, n);
    delete[] exArr;
}
