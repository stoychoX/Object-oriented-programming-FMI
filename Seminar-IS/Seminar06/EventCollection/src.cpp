#include "EventManager/EventManager.h"
#include <iostream>

int main()
{
    EventManager manager;

    manager.addEvent({
        "Activity 1",
        27, 3, 2024,
        10, 0, 0,
        16, 0, 0
    });

    manager.addEvent({
        "Activity 2",
        31, 3, 2024,
        17, 0, 0,
        22, 00, 00
    });

    const Event& first = manager.at(0);
    first.print();

    int idx = manager.find("Activity 2");
    if(idx == -1)
    {
        std::cout << "No activity...";
    }
    else
    {
        manager.at(idx).print();
    }
}