#include <iostream>

class Entity1
{
public:
	Entity1()
	{
		std::cout << "Constructor E1 called" << std::endl;
	}

	~Entity1()
	{
		std::cout << "Destructor E1 called" << std::endl;
	}
};

class Entity2
{
public:
	Entity2()
	{
		std::cout << "Constructor E2 called" << std::endl;
	}

	~Entity2()
	{
		std::cout << "Destructor E2 called" << std::endl;
	}
};

class Entity
{
	Entity1 e1;
	Entity2	e2;
public:
	Entity()
	{
		std::cout << "Constructor E called" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destructor E called" << std::endl;
	}
};

void drawLine()
{
	std::cout << std::endl << "==========================" << std::endl;
}

int main()
{
	{
		Entity1 e;
	}
	drawLine();

	Entity1* e;
	{
		e = new Entity1;
	}

	delete e;

	drawLine();
	{
		Entity1 arr[20];
	}

	drawLine();

	Entity e2;
}