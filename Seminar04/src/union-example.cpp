#include <iostream>

union Example
{
    int x;
    short y;
    char z;

    char bytes[4];
};

void showBytes(const Example& e, const char* message)
{
    std::cout << message << std::endl;
    std::cout << "Bytes as integers: ";

    for (size_t i = 0; i < 4; i++)
        std::cout << (int)(e.bytes[i]) << " ";

    std::cout << std::endl;
    std::cout << "Bytes as characters: ";
    
    for (size_t i = 0; i < 4; i++)
        std::cout << e.bytes[i] << " ";
    std::cout << std::endl << std::endl;
}

int main()
{
    Example e;

    Example e;
    showBytes(e, "After creating new (uninitialized) union.");
    
    e.z = 'A';
    showBytes(e, "After changing the char variable to 'A'");

    e.x = 65;
    showBytes(e, "After changing the int variable to 65 (the ascii code of 'A')");

    e.z = 'B';
    showBytes(e, "After changing the char variable to 'B'");
}