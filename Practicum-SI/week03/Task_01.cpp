#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996);

struct Example
{
    int data;
    char buff[8];
};

Example *readExamples(int n)
{
    Example *examples = new Example[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> examples[i].data;
        std::cin.ignore();
        std::cin >> examples[i].buff;
    }
    return examples;
}

void addExamplesToFile(std::ofstream &ofs, const Example *examples, int n)
{
    ofs.write((const char *)examples, n * sizeof(Example));
}

size_t getFileSize(std::ifstream &ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    ifs.seekg(currentPos);
    return fileSize;
}

size_t examplesInFile(std::ifstream &ifs)
{
    if (!ifs.is_open())
    {
        std::cout << "Error while opening file";
        return 0;
    }
    return getFileSize(ifs) / sizeof(Example);
}

Example getSearchedExample(std::ifstream &ifs, const char *pattern, size_t count)
{
    Example *examples = new Example[count];
    ifs.read((char *)examples, count * sizeof(Example));
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(examples[i].buff, pattern) == 0)
        {
            Example result = examples[i];
            delete[] examples;
            return result;
        }
    }
    delete[] examples;
    return {-1, "err"};
}

int main()
{
    int n;
    std::cin >> n;
    char fileName[1024];
    std::cin.ignore();
    std::cin.getline(fileName, 1024);
    std::ofstream ofs(fileName, std::ios::out | std::ios::binary | std::ios::app);
    if (!ofs.is_open())
    {
        std::cout << "Error while opening file";
        return 0;
    }

    Example *examples = readExamples(n);
    addExamplesToFile(ofs, examples, n);
    ofs.close();
    std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
    size_t countExamples = examplesInFile(ifs);
    char toSearch[1024];
    std::cin.ignore();
    std::cin.getline(toSearch, 1024);
    Example searchedExample = getSearchedExample(ifs, toSearch, countExamples);
    std::cout << searchedExample.buff << " " << searchedExample.data;
    ifs.close();
    delete[] examples;
    return 0;
}
