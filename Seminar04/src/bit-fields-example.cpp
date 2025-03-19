#include <iostream>

struct BitFieldExample
{
    // We can only use 3 bits of the 32 bit
    // unsigned variable! Rest are padding.
    unsigned b : 3;
};

int main()
{
    BitFieldExample b {6};

    std::cout << b.b++ << " " << b.b++ << " " << b.b;
}