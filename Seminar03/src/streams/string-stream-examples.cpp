#include <iostream>
#include <sstream>
#include <cassert>

void string_stream_examples()
{
    // Stream for text manipulation.
    // Supports both input and output operations.
    std::stringstream ss;

    ss << "123";
    int x = 0;

    ss >> x;

    // Easy way to convert string to number!
    assert(x == 123);

    ss << x;
    std::cout << ss.str() << std::endl; // 123 - easy way to convert number to string!

    // Only output operations.
    std::ostringstream oss;

    oss << "One of the numbers we used is " << x << " and its a good number" << std::endl;

    // Easy and fast way for string concatenation!
    std::cout << oss.str();

    std::istringstream iss("3 4 5");

    while(!iss.eof())
    {
        int x = 0;
        iss >> x;
        std::cout << x << " ";
    }
}

int main()
{
    string_stream_examples();
}