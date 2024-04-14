#include <iostream>
#include "SelfCounting.h"

int main()
{
    SelfCounting fst;
    
    {
        SelfCounting snd;
        std::cout << SelfCounting::getAliveObjectsCount() << " " << SelfCounting::getCreatedCount() << std::endl; 
    }

    std::cout << SelfCounting::getAliveObjectsCount() << " " << SelfCounting::getCreatedCount() << std::endl; 
}