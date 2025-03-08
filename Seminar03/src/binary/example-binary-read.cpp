#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
    std::ifstream inFile("test.dat", std::ios::binary);

    if(!inFile.is_open())
    {
        std::cout << "Cannot find file" << std::endl;
        return -1;
    }

    char buffer[16]{};
    inFile.read(buffer, 10);

    std::cout << buffer << std::endl;

    int x = 0;
    inFile.read((char*)(&x), sizeof(int));

    std::cout << x << std::endl;

    int arr[4] {};
    inFile.read((char*)(arr), 4 * sizeof(int));

    for (size_t i = 0; i < 4; i++)
    {
        std::cout << arr[i] << " ";
    }
    
}