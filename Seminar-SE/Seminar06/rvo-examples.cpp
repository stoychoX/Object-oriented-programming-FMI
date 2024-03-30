#include <iostream>

class Entity
{
public:
    int x = 0;

    Entity() 
    {
        std::cout << "Default constructor" << std::endl;
    }

    Entity(const Entity& other)
    {
        std::cout << "Copy constructor" << std::endl;
    }
};

Entity foo()
{
    return Entity();
}

Entity bar()
{
    Entity e2;
    return e2;
}

int main()
{
/*
    if no rvo is applied the output would be
    Default constructor
    Copy constructor
    Copy constructor
    Default constructor
    Copy constructor
    Copy constructor
*/

    Entity e = foo();
    Entity e1 = bar();
/*
    with rvo we get
    Default constructor
    Default constructor
*/
}