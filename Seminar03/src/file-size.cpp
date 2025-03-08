#include <iostream>
#include <fstream>

unsigned getFileSize(std::ofstream& out)
{
    unsigned currentPosition = out.tellp();
    out.seekp(0, std::ios::end);
    unsigned fileSize = out.tellp();
    out.seekp(currentPosition, std::ios::beg);

    return fileSize;
}

int main()
{
    std::ofstream outFile("file-size.cpp", std::ios::binary | std::ios::app);


    std::cout << getFileSize(outFile);
}