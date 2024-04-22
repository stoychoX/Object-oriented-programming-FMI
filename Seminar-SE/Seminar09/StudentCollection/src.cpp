#include <iostream>
#include "StudentCollection.h"
#include <string>

String to_string(size_t s)
{
    return String(std::to_string(s).c_str());
}

int main()
{
    StudentCollection sc;
    size_t idx = 0;
    for (size_t i = 0; i < 300; i+=3)
    {
        sc.push({"Name" + String("_") + to_string(i), 10});
        sc.push({"Name" + String("_") + to_string(i + 1), 10});
        sc.push({"Name" + String("_") + to_string(i + 2), 10});
    }


    for (size_t i = 0; i < 300; i+=2)
    {
        sc.removeAt(i);
    }
    

    for (size_t i = 0; i < sc.getCapacity(); i++)
    {
        if(sc.contains(i))
            std::cout << sc.at(i).getName() << std::endl;
    }
    
}