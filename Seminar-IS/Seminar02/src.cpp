#include <iostream>
#include <fstream>

int main()
{
    std::ifstream inFile("test-file.txt");
    // Ще създаде обект от тип ifstream
    // и ще се опита да отвори поток за четене от файла test-file.txt.

    if(inFile.is_open())
        std::cout << "The file is open";
    else
        std::cout << "Cant open file";

}