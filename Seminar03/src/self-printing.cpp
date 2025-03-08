#include <iostream>
#include <fstream>

void printFile(const char* fileName)
{
    std::ifstream inFile(fileName);

    if(!inFile.is_open())
    {
        std::cout << "Can't find file " << fileName;
        return;
    }

    while (!inFile.eof())
    {
        char buff[64]{};
        inFile.getline(buff, 64);
        std::cout << buff << std::endl;
    }
    
    inFile.close();
}

int main()
{
    printFile("self-printing.cpp");
}