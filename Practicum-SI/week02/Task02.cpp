#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

int GetCharCountFromFile(const char* fileName)
{
    int count = 0;
    char ch;

    ifstream ifs(fileName);

    if (!ifs.is_open())
        return -1;

    while (true)
    {
        ch = ifs.get();

        if (ifs.eof())
        {
            ifs.clear();
            return count;
        }

        if (ch == 'a' || ch == 'd')
            continue;

        count++;
    }

    ifs.close();
}

int main()
{
    //cout << GetCharCountFromFile("test.txt");
}
