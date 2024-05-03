#include "StringView.h"
#include <iostream>

int main()
{
    String str = "Hello world!";

    StringView view(str);

    std::cout << view << std::endl;

    view.remove_prefix(2);

    std::cout << view << std::endl;

    view.remove_suffix(2);

    std::cout << view << std::endl;

    StringView subView = view.substr(1, 4);

    std::cout << subView << std::endl;

    std::cout << subView[1] << std::endl;

    try
    {
        view.at(100);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }

    for (size_t i = 0; i < 100; i++)
        view.remove_prefix(1); // Making sure this won't break 

    std::cout << view.empty() << std::endl;   
}