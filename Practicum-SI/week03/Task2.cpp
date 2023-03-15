#include <iostream>
#include <fstream>
#include <string>

struct Example 
{
    int data;
    char buff[8];
};
size_t getFileSize(std::ifstream& ifs)
{
    size_t currentPosition = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    ifs.seekg(currentPosition);
    return fileSize;
}
size_t examplesInFile(std::ifstream& ifs, const char* filePath)
{

    if (!ifs.is_open())
    {
        return 0;
    }
    size_t examplesInFile = getFileSize(ifs) / sizeof(Example);

    return examplesInFile;
}
Example FindExampleWithPatternBuff(std::ifstream& ifs, const char* fileName, const char* pattern)
{
    Example errorExample{ -1,"IFS_ERR" };
    if (!ifs.is_open())
    {
        return errorExample;
    }
    strcpy_s(errorExample.buff, sizeof(errorExample.buff), "err");

    Example buffExample;
    while (true)
    {
        ifs.read((char*)& buffExample, sizeof(Example));
        if (ifs.eof())
        {
            return errorExample;
        }
        if (strcmp(pattern, buffExample.buff) == 0)
        {
            return buffExample;
        }
        
    }
}
int main()
{
    char fileName[1024];
    std::cin.getline(fileName, 1024);
    std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
    std::cout << examplesInFile(ifs, fileName);
    std::cout << std::endl;
    char pattern[1024];
    std::cin.getline(pattern, 1024);
    std::cout << std::endl;
    Example example = FindExampleWithPatternBuff(ifs, fileName, pattern);
    std::cout << example.data << " " << example.buff << std::endl;
}