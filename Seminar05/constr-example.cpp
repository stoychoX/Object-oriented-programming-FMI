#include <iostream>
#include <iostream>

class Entity1
{
private:
	int _x;
public:
	Entity1() : _x(0)
	{
		std::cout << "Default constructor of E1 called." << std::endl;
	}
	Entity1(int x) : _x(x)
	{
		std::cout << "Parameter constructor of E1 called." << std::endl;
	}
};


class Entity2
{
private:
	int _y;
public:
	Entity2() : Entity2(0) // Можем да извикваме други конструктори.
	{
		std::cout << "Default constructor of E2 called." << std::endl;
	}
	Entity2(int y) : _y(y)
	{
		std::cout << "Parameter constructor of E2 called." << std::endl;
	}
};

class Entity
{
private:
	Entity1 e1;
	Entity2 e2;
public:
};

class Entity3
{
private:
	Entity1 e1;
	Entity2 e2;
public:
	Entity3(int x, int y) : e1(x), e2(y) {}
};

void drawLine()
{
	std::cout << std::endl << "==========================" << std::endl;
}

int main()
{
	{
		// Извикване на конструктор по подразбиране
		Entity1 e1;

		// Извикване на конструктор с параметри
		Entity2	e2(10);
		drawLine();
	}

	{
		// Когато не дефинираме конструктор по подразбиране компилатора създава
		Entity e;
		// Обърнете внимание как се извеждат член-данните.
		drawLine();
	}

	{
		// Entity3	e; Това е грешка ако имаме конструктор с параметри не се създава default
		Entity3	e(10, 20); // Извикват се правилните конструктори.
		drawLine();
	}
	
	{
		// Извикват се 20 конструктора
		Entity1 e1[20];
		drawLine();
	}

	{
		Entity1* e2;
		// нищо не се извиква
		e2 = new Entity1; // конструктор по подразбиране

		delete e2;

		e2 = new Entity1(1); // Конструктор с параметри
		delete e2;
		drawLine();
	}
}