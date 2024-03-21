#include <iostream>
#include <fstream>

void copyFile(const char* sourcePath, const char* destinationPath)
{
    std::ofstream outFile(destinationPath);
    std::ifstream inFile(sourcePath);

    if(!inFile.is_open())
        return;

    if(!outFile.is_open())
        return;
    
    while(true)
    {
        char currentChar = inFile.get();
        
        if(inFile.eof())
            break;
        
        outFile.put(currentChar);
    }
}

int main()
{
    copyFile("copyFile.cpp", "test.cpp");
}
