#include <iostream>
#include <fstream>

void copyFile(const char* sourcePath, const char* destinationPath)
{
    std::ofstream outFile(destinationPath);
    std::ifstream inFile(sourcePath);

    if(!inFile.is_open())
        return;

    while(true)
    {
        char currentChar = inFile.get();
        
        if(inFile.eof())
            break;
        
        outFile.put(currentChar);
    }
}

void copyFileSecond(const char* sourcePath, const char* destinationPath)
{
    std::ofstream outFile(destinationPath);
    std::ifstream inFile(sourcePath);

    if(!inFile.is_open())
        return;

    char buff[1024] = {};

    while(true)
    {
        inFile.getline(buff, 1024);
        outFile << buff << '\n';
        if(inFile.eof())
            break;
    }
}

int main()
{
    copyFileSecond("copyFile.cpp", "test.cpp");
}