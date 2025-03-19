#include <iostream>

enum class VariantType
{
    Int,
    Char
};

union VariantData
{
    int number;
    char symbol;
};

struct IntCharVariant
{
    VariantType type;
    VariantData data;
};

IntCharVariant createIntVariant(int data)
{
    return { VariantType::Int, data };
}

IntCharVariant createCharVariant(char data)
{
    return { VariantType::Char, data };
}

void printVariant(const IntCharVariant& v)
{
    if(v.type == VariantType::Int)
    {
        std::cout << "The number is: " << v.data.number;
    }
    else if(v.type == VariantType::Char)
    {
        std::cout << "The symbol is: " << v.data.symbol;
    }
}

int main()
{
    
}