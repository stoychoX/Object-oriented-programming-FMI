# Десети семинар по обектно ориентирано програмиране - СИ

## Теоретични примери
1. Ще се компилира ли следния код:
```cpp
#include <iostream>
class A {
public:
	void f() {
		std::cout << "F" << std::endl;
	}
};

class B : A {};

void f(A& a) {
	a.f();
}

int main() {
	B b;
	f(b);
}
```

2. Ще се компилира ли следния код
```cpp
#include <iostream>
class A {
public:
	void f() {
		std::cout << "F" << std::endl;
	}
};

class B : public A 
{
public:
	void f() {
		std::cout << "B::f" << std::endl;
	}
};

void f(A& a) {
	a.f();
}

int main() {
	B b;
	f(b);
}
```

3. Ще се компилира ли следния код
```cpp
#include <iostream>
class Base {
protected:
	int baseInt;
public:
	Base(int x) : baseInt(x) {}
};

class DerStatic : public Base {
protected:
	char pass[8];
public:
	DerStatic(const char arg[8], int x) : Base(x) {
		strcpy(pass, arg);
	}
};

class DerDynamic : public DerStatic {
	char* name;

	void free() { 
		delete[] name; 
	}
	void copyFrom(const DerDynamic & other) {
		int len = strlen(other.name);
		this->name = new char[len + 1];
		strcpy(this->name, other.name);
	}
public:
	DerDynamic(const char* name, const char pass[8], int x) : DerStatic(pass, x)
	{
		int len = strlen(name);
		this->name = new char[len + 1];
		strcpy(this->name, name);
	}
	DerDynamic(const DerDynamic& other) { 
		copyFrom(other); 
	}

	DerDynamic& operator=(const DerDynamic& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}
	~DerDynamic() {
		free();
	}
};
int main() {
	DerDynamic d("text", "1223344", 10);
}
```

4. Кои от следните примери ще успеят
```cpp
class A {
public:
	int a;
};
class B : public A {
public:
	int b;
};

void f(A obj) {
	obj.a = 5;
	obj.b = 6;
}
void g(A& obj) {}
void h(A* obj) {}
void k(B& obj) {}

int main() {
	A obj1;
	B obj2;

	f(obj1); 
	f(obj2); 

	g(obj1);
	g(obj2);

	h(&obj1);
	h(&obj2);

	k(obj1);
	k(obj2);
}
```

## Задача първа
Имплементирайте клас за множество от естествени числа по критерий. Класът трябва да приема в конструктора цяло число - максималното число, което може да се запази в множеството и една булева функция: за включване на число (тези, които да са елементи на множеството). Трябва да имате функции за проверка дали число е в множеството (за константно време), за връщане на броя на елементите и за принтиране на множеството.

Трябва да разполагате с интерфейс за промяна на критериите - setInclude и setExclude.

Примерен интерфейс:
```cpp

int main()
{
   SetByCriteria s(11, [](unsigned i) {return i % 2 == 0; });

   s.print(); // {0, 2, 4, 6, 8, 10}
   s.contains(1); // false
}
```


Имплементирайте и клас за множество по стринг. Множество, което в конструктора приема цяло число - максималното число, което може да се запази в множеството и символен низ - числата, които да се запазят, разделени с интервал. Трябва да имате функция за промяна на стринга, както и за промяна на символ по индекс. Трябва да имате и функции за проверка дали число е в множеството (за константно време), за връщане на броя на елементите и за принтиране на множеството.

Примерен интерфейс:

```cpp
int main()
{
   SetByString s(300, "1 2 3");

   s.print(); // {1, 2, 3}
   
   s.setAt(1, '1');
   
   s.print(); // {3, 112}
}
```