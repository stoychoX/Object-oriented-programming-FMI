#include <iostream>
#include <fstream>

void printFile(const char* path)
{
    std::ifstream inFile(path);
    
    if(!inFile.is_open())
        return;
    
    while (true)
    {
        char ch = inFile.get();
        if(inFile.eof())
            break;
        
        std::cout << ch;
    }
}

int main()
{
    printFile("printMyCode.cpp");
}