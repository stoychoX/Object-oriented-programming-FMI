#include <iostream>
#include <fstream>

void printFormatted(const char* sourcePath, const char* destinationPath)
{
    std::ifstream inFile(sourcePath);
    std::ofstream outFile(destinationPath);

    if(!inFile.is_open())
        return;
    
    if(!outFile.is_open())
        return;

    char buff[64] = {};

    while (true)
    {
        inFile >> buff;

        outFile << buff;
    
        if(inFile.eof())
            break;
        
        outFile << ",";
    }
}

int main()
{
    printFormatted("test-file.txt", "formatted-file.txt");
}