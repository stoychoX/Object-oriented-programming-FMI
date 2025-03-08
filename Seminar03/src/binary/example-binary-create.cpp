#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
    std::ofstream outFile("test.dat", std::ios::binary);

    if (!outFile.is_open())
        return 1;

    int x = 42;
    const char* text = "Dump me!!!";

    // We can write text:
    outFile.write(text, strlen(text) /* how many bytes? strlen bytes! */);

    // We can write variables (but with cast!)
    outFile.write((const char*)(&x), sizeof(int) /* how many bytes? sizeof(int) bytes! */);

    int arr[4] = { 1, 2, 3, 4 };

    // We can write arrays!!!
    outFile.write((const char*)(arr), 4 * sizeof(int)/* We have 4 ints here. */);
}