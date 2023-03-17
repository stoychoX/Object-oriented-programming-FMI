#include<iostream>

struct A {
	A() {
		std::cout << "constr of A" << std::endl;
	}

	~A() {
		std::cout << "destr of A" << std::endl;
	}
};

struct B {
	int x;

	B() {
		std::cout << "constr of B" << std::endl;
	}

	B(int y) {
		std::cout << "param constr of B" << std::endl;
		x = y;
	}

	~B() {
		std::cout << "destr of B" << std::endl;
	}
};

struct C {
	A a;
	B b;

	C() {
		std::cout << "Constr of c" << std::endl;
	}

    ~C() {
		std::cout << "destr of C" << std::endl;
	}
};

int main() {
    A* ptr;
	{
        A a;            // Конструктор на а
        ptr = new A;    // Конструктор на *ptr
    }                   // Деструктор на a

    delete ptr; // деструктор на ptr
    
    std::cout << std::endl;

    C obj[20]; // 20 конструктора на obj. Вика се първо на А после на B и след това на С.
}              // 20 деструктора на С. Вика се първо този на С после този на В и накрая този на А
