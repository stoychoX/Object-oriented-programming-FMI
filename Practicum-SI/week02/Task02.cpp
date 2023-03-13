#include <iostream>
#include <fstream>

size_t count(const char *fileName)
{
    std::ifstream inputStream(fileName);
    if (!inputStream.is_open())
    {
        std::cerr << "Error";
        return 0;
    }
    size_t count = 0;
    while (true)
    {
        char current = inputStream.get();
        if (current != 'a' || current != 'd')
        {
            count++;
        }
        if (inputStream.eof())
        {
            break;
        }
    }
    return count;
    inputStream.close();
}
int main()
{

    return 0;
}
