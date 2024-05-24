#include <iostream>
#include "optional.hpp"

int main()
{
    Optional<int> opt;
    std::cout << opt.has_value() << std::endl;
    opt = 10;

    std::cout << opt.has_value() << std::endl;

    std::cout << opt.value() << " " 
              << *opt << " " << opt.value_or(42) << std::endl;

    opt.reset();

    std::cout << opt.value_or(42) << std::endl;

}