# Задачи и теория - подготовка за контролно 2 на Софтуерно Инженерство

## Част 1 - теоретични въпроси

<details>
<summary> <b>Задача първа</b> </summary>
Ще се компилират ли следните примери?

```c++
int a = 5;
```

```c++
int &r1 = a * 10;
```

```c++
int &&r2 = a * 10;
```

```c++
const int &r3 = a * 10;
```
</details>

<details>
<summary> <b> Задача втора </b> </summary>

#### Ще се извика ли деструктура в този код?

```c++
class A {
	~A() {
		std::cout << "Destr" << std::endl;
	}
};

void f() {
	A a;
	throw std::exception();
}

int main() {
	f();
	return 0;
}
```

```c++
class A {
	~A() {
		std::cout << "Destr" << std::endl;
	}
};

void f() {
	A a;
	throw std::exception();
}

int main() {
	try {
		f();
	} catch (...) {
		std::cout << "Unknown error"<< std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception"<< std::endl;
	}

	return 0;
}
```

```c++
class A {
	~A() {
		std::cout << "Destr" << std::endl;
	}
};

void f() {
	A* a = new A();
	throw std::exception();

	delete a;
}

int main() {
	try {
		f();
	} catch (...) {	} 
	
	return 0;
}
```
</details>

<details>
<summary> <b> Задача трета </b> </summary>

#### Има ли проблем в следния код?

```c++
class MyClass {
	static int unique_id = 0;
	
public:
	MyClass() {
		unique_id++;
	}
};
```
</details>

<details>
<summary> <b> Задача четвърта </b> </summary>

#### Какво ще се изведе на конзолата?

```c++
#include<iostream>

void g(int&&) {
	std::cout << "RValue";
}

void g(int&) {
	std::cout << "LValue";
}

void f(int&& a) {
	g(a);
}

int main() {
	int i = 0;

	f(std::move(i));
}
```

</details>

<details>
<summary> <b> Задача пета </b> </summary>

#### Коя от функциите ще се извика?

```c++
class A {};

class B : public A  {};

void f(A& obj);
void k(A&& obj);
void g(A* ptr);
void t(B& obj);

int main() {
	A obj1;
	B obj2;

	f(obj1);
	f(obj2);

	k(std::move(obj1));
	k(std::move(obj2));

	g(&obj1);
	g(&obj2);

	t(obj2);
	t(obj1);

	return 0;
}
```

</details>

<details>
<summary> <b> Задача шеста </b> </summary>

```c++
class A {
	int a;

public:
	A(int a) : a(a) {}
	void f() const {
		std::cout << a;
	}
};

template <typename T>
void g(const T& t) {
	t.f();
}

int main() {
	g<A>(5);
	return 0;
}
```

</details>

<details>
<summary> <b> Задача седма </b> </summary>

Какво ще изведе кодът на конзолата?

```c++
#include<iostream>

template<class K, class V>
struct Entity {
	void print(const K& k, const V& v) {
		std::cout << k + v;
	}
};

template<class T>
struct Entity<int, T> {
	void print(int k, const T& t) {
		std::cout << 2 * k + t;
	}
};

int main() {
	Entity<int, int> e;
	e.print(2, 3);
}
```

</details>

<details>
<summary> <b> Задача осма </b> </summary>

Има ли проблеми в следния код?

```c++
#include <iostream>

class A {};

template<typename T>
T add(T a, T b) {
	return a + b;
}

int main() {
	int result1 = add(5, 10);
	double result2 = add(3.14, 2.5);
	A obj = add(A(), A());
	
	return 0;
}
```

</details>

<details>
<summary> <b> Задача девета </b> </summary>

Има ли проблем в кода?

```c++
class B : public A {
public:
	B(...) : A(...)
	{...}
	
	B::B(const B& other) {
		copyFrom(other);
	}

	B& B::operator=(const B& other) {
		if (this != &other) {
			A::operator=(other);
			free();
			copyFrom(other);
		}
		return *this;
	}

	~B() {
		free();
	}
};
```

</details>

<details>
<summary> <b> Задача десета </b> </summary>

Има ли проблем в кода?
```c++
#include <iostream>

class Animal {
public:
	virtual void makeSound() = 0;
};

class Dog : public Animal {
	char* breed;

public:
	void makeSound() override {
		std::cout << "Woof!" << std::endl;
	}
//big 6

};

class Cat : public Animal {
public:
	void makeSound() override {
		std::cout << "Meow!" << std::endl;
	}
};

int main() {
	Animal* animal1 = new Animal();
	Animal* animal2 = new Dog();
	Animal* animal3 = new Cat();
	
	animal1->makeSound();
	animal2->makeSound();
	animal3->makeSound();
	
	delete animal1;
	delete animal2;
	delete animal3;

	return 0;
}
```

</details>

<details>
<summary> <b> Задача единадесета </b> </summary>

Какво ще изведе следния фрагмент?

```c++
#include<iostream>

struct E {
	virtual ~E() = default;
};

int main() {	
	std::cout << sizeof(E);
}
```

</details>

<details>
<summary> <b> Задача дванадесета </b> </summary>

Какво съдържат виртуалните таблици на следните структури:

```c++
struct A {
	virtual void f();
	virtual void g();
	void k();
};

struct B : public A {
	void f() override;
	virtual void h();
};

struct C : public B {
	int f() override;
};
```

```c++
struct A {
	virtual void f() final;
	virtual void g() final;
	void k();
};

struct B : public A {
	void f() override;
	virtual void h();
};

struct C : public B {
	int f() override;
};
```

</details>

<details>
<summary> <b> Задача тринадесета </b> </summary>

Има ли проблем следния код?

```c++
#include<iostream>

int main() {
	UniquePtr p1(new int(10));
	UniquePtr p2(p1);
}
```

</details>

<details>
<summary> <b> Задача четиринадесета </b> </summary>

Има ли проблем следния код?

```c++
#include<iostream>

int main() {
	int* n = new int(10); 
	SharedPtr p1(n);
	SharedPtr p2(n);
}
```

</details>

<details>
<summary> <b> Задача петнадесета </b> </summary>

Има ли проблем следния код?

```c++
#include<iostream>

struct A {
	int x;
	
	A(int _x) : x(_x) {}
};

struct B : public A {
	int y;

	B(int _x, int _y) : A(_x), y(_y) {}
};

struct C : public B {
	int z;
	
	C(int _x, int _y, int _z) : A(_x), B(x, _y), z(_z){}
};

int main() {
	C c(1, 2, 3);
	std::cout << c.z;
	return 0;
}
```
</details>

## Част 2 - задачи

### **Задача първа**
Да се реализира система за провеждане на тестове. Всеки тест се състои от следните типове въпроси:

- **YesNoQuestion**, който описва въпрос с два възможни отговора: да или не. При конструиране се задават текст (до 1024 символа), точки и верен отговор. Въпросът дава 0 т. при грешен и пълен брой точки при верен отговор.

- **MultipleChoice**, който описва въпрос с няколко възможни отговора (до 5), от които някои са верни. При конструиране се задават текст (до 1024 символа), точки x, възможни и верни отговори. Всеки правилно посочен отговор добавя x точки, а всеки погрешно посочен отговор отнема x точки.

- **OpenQuestion**, който описва въпрос със свободен текст. При конструиране се задават текст и брой точки. При оценяване се извеждат въпроса и отговора и се въвежда оценка в проценти. 

Да се реализира клас **Test**, представящ тест с въпроси от всякакъв вид. Да се реализират функциите:

* `addQuestion`, която добавя нов въпрос към теста;

* `doTest`, която задава всички въпроси подред и събира отговорите им;

* `gradeTest`, която оценява теста и връща броя събрани точки.


### **Задача втора**
Нека `процедура`, в контекста на задачата, наричаме функция от следния вид:

```cpp
void procedureExample(T&);
```

където `T` e произволен тип. Процедурата може да променя аргументите си. Разбира се, процедурата може да извиква други процедури вътре в себе си.

Да се имплементира полиморфна йерархия, представляваща изпълнението на процедура. Процедурата може да е проста (не извиква в себе си други процедури) или съставна (извиква краен брой процедури).
