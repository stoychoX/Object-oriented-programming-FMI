## Eдинадесети семинар по обектно ориентирано програмиране - 15.05.2025

## Статично свързване (static dispatch).
Нека разгледаме следния пример:
```cpp
class Base
{
public:
	void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}
};

class Der : public Base
{
public:
	void f() const
	{
		std::cout << "Der::f()" << std::endl;
	}
};
```

Този пример ще се компилира. Първоначално изглежда объркващо, понеже имаме две публични функции, които се казват `f()`. Всъщност, въпреки че имената им са едни и същи, те принадлежат на два различни класа. Можем да си мислим за `Base::f()` и за `Der::f()`.

Нека сега разгледаме този пример:
```cpp
void foo(const Base& b)
{
	b.f();
}

int main()
{
	Base b;
	Der d;

	foo(b);
	foo(d);
}
```

Какво ще се изведе в случая? Знаем, че на мястото на родител можем да подадем негов наследник, та това ще се компилира. Дали ще се извикат две различни функции или винаги ще се извика функцията на `Base`?
Програмата извежда следното:
```
Base::f()
Base::f()
```

Това е очаквано. Все пак компилаторът вижда, че на функцията `foo` се подава обект от тип `Base`. В случая той избира коя функция да извика **по време на компилация**. Това се нарича **статично свързване**.

Нека разгледаме още един подобен пример:
```cpp
struct A
{ 
    void f() const 
    {
	    std::cout << "A::f()" << std::endl;
    }	
};

struct B : public A
{
    void f() const 
    {
	    std::cout << "B::f()" << std::endl;
    }	
};

int main()
{
	B* bPtr = new B();

	A* aPtr = bPtr;
	
	bPtr->f(); // B::f()
	aPtr->f(); // A::f()
	
	delete bPtr;
}
```

В случая компилатора преценя коя функция да извика **съдейки по типа на указателя.** За едно и също парче памет в два различни контекста имаме две различни поведения.

Грешно ли е това? Не. Това си е в реда на нещата. Въпросът е какво правим когато искаме това поведение да се промени. Какво правим когато **искаме изборът на това коя функция се извиква да се прави по време на изпълнение на програмата и да зависи от типа на обекта.**

## Динамично свързване (dynamic dispatch). Ключовата дума `virtual`
*Dynamic dispatch in C++ refers to the mechanism by which the appropriate function to call for a particular method is determined at runtime, based on the type of object being referenced.*

Ако в горните примери функцията `f()` имаше диманимчно свързване изходът на програмата щеше да е друг. **Казваме на компилатора, че една функция има динамично свързване чрез ключовата дума virtual!**. Нека разгледаме как бихме накарали функцията `f()` в първия пример да има динамично свързване:
```cpp
#include <iostream>

class Base
{
public:
	virtual void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}
};

class Der : public Base
{
public:
	void f() const override
	{
		std::cout << "Der::f()" << std::endl;
	}
};

void foo(const Base& b)
{
	b.f();
}

int main()
{
	Base b;
	Der d;

	foo(b);
	foo(d);
}
```

Сега вече изходът е:
```
Base::f()
Der::f()
```

Отново: с `virtual` означаваме функция, която има динамично свързване. Ако функцията не е декларирана като `virtual` тя има статично свързване. Нито едно от двете свързвания не е грешно - всяко едно от тях си има предназначение!

Какво прави ключовата дума `override`? Можем ли да постигнем динамично свързване без нея? Отговорът е да, можем. Тя е въведена в езика **за да ни помага** а не за да ни пречи. `override` обещава, че **в родителя има функция, която има динамично свързване, и ние променяме нейното поведение за текущия клас.** Защо ни помага? Все пак ние пишем кода, ясно ни е, че такава функция има. И все пак ако объркаме декларацията на функцията компилатора няма да ни се скара:

```cpp
class Base
{
public:
	virtual void f() const
	{
		std::cout << "Base::f()" << std::endl;
	}
};

class Der : public Base
{
public:
	void f()
	{
		std::cout << "Der::f()" << std::endl;
	}
};
```
Това е валиден код, но не прави точно това което искаме. Тук функцията `Der::f()` не е динамично свързана понеже функцията в бащата е `Base::f() const` и двете функции са различни. Това ще се компилира и най-вероятно ще ни остави заблудени, че `f()` е динамично свързана.

Ако добавим `override` след `f()` в `Der` компилатора вече ще ни се скара! Ще ни каже, че не намира такава функция в родителя и ние спокойно ще си добавим липсващия `const`.

## Полиморфизъм
*Едно и също име се реализира по различен начин.*
*Едно име много имплементацции.*

Полиморфизмът е ключова концепция в обектно ориентираното програмиране.
В езика С++ има два типа полиморфизъм: **Runtime polimorphism** и **Compile time polymorphism**.

Някои примери за compile time полиморфизъм са:
* Function overloading
* Operator overloading
* Templates

Пример за runtime polymorphism е динамичното свързване. 

Когато имаме **полиморфна йерархия** можем да съхраняваме всеки един от наследниците като указател към някой от предшествениците му!
```cpp
#include <iostream>
using namespace std;

struct A
{
    virtual void f() const 
    {
		std::cout << "A::f()" << std::endl;
    }	
};

struct B : public A
{
    void f() const 
    {
       std::cout << "B::f()" << std::endl;
    }	
};

struct C : public A
{
    void f() const 
    {
       std::cout << "C::f()" << std::endl;
    }	
};

int main()
{
	A* ptrs[3];
	A obj1;
	B obj2;
	C obj3;
	
	ptrs[0] = &obj1;
	ptrs[1] = &obj2;
	ptrs[2] = &obj3;
	
	ptrs[0]->f(); // A::f()
	ptrs[1]->f(); // B::f()
	ptrs[2]->f(); // C::f()
}
```
В примера всеки указател от масива може да сочи към всеки наследник (пряк или косвен) на A. 

**Важно:** когато имаме някаква полиморфна йерархия ще изтриваме обектите чрез базов указател. **За да се извикват правилните деструкори задължително деструкторът на базовият клас трябва е деклариран като виртуален!**

```cpp
#include<iostream>

struct Animal
{
	virtual void sayHello() const
	{
		std::cout << "Hello, I am a random animal" << std::endl;
	}

	virtual ~Animal(){} //!!!
};
struct Dog : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a dog!" << std::endl;
	}
};

struct Cat : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a cat!" << std::endl;
	}
};

struct Mouse : public Animal
{
};

int main()
{
	Animal** animals = new Animal*[3];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Mouse();


	//from base-class pointer
	animals[0]->sayHello(); // Hello, I am a dog!
	animals[1]->sayHello(); // Hello, I am a cat!
	animals[2]->sayHello(); // Hello, I am a random animal!

	delete animals[0];
    delete animals[1];
    delete animals[2];
	delete[] animals;
}
```

## Абстрактен клас
Можем да дефинираме и така наречените **чисто виртуални функции.** Тяхната цел е да бъдат имплементирани в наследниците и да служат като описание на интерфейса им.

```cpp
#include<iostream>

struct Animal
{
	virtual void sayHello() const = 0;


	virtual ~Animal(){} //!!!
};
struct Dog : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a dog!" << std::endl;
	}
};

struct Cat : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a cat!" << std::endl;
	}
};

struct Mouse : public Animal
{
	void sayHello() const override
	{
		std::cout << "Hello, I am a mouse!" << std::endl;
	}
};

struct PrehistoricAnimal : public Animal
{};

int main()
{
	// Animal* pa1 = new Animal(); No! Animal is an abstract class!
	// Animal* pa2 = new PrehistoricAnimal(); No! PrehistoricAnimal is also an abstract class!

	Animal** animals = new Animal*[3];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Mouse();


	//from base-class pointer
	animals[0]->sayHello(); // Hello, I am a dog!
	animals[1]->sayHello(); // Hello, I am a cat!
	animals[2]->sayHello(); // Hello, I am a mouse!

	delete animals[0]
	delete animals[1]
	delete animals[2];
	delete[] animals;
}
```

Абстрактен клас наричаме **клас, който има поне една чисто виртуална функция. Не можем да създаваме инстанции от абстрактни класове!**

Обикновено чисто виртуалните функции нямат имплементация в абстрактния клас. Езикът все пак не ни спира да направим имплементация. Тази имплементация не може да бъде извикана от инстанция. Но можем да я извикаме от наследник!

```cpp
#include <iostream>

class Base
{
public:
	virtual void execute() const = 0;
	virtual ~Base() = default;
};

void Base::execute() const 
{
	std::cout << "Execute base" << std::endl;
}

class Derived : public Base
{
public:
	void execute() const override;
	virtual ~Derived() = default;
};

void Derived::execute() const
{
	Base::execute();
	std::cout << "Execute derived" << std::endl;
}

int main()
{
	Base* d = new Derived;
	d->execute();
	delete d;
}
```

Идеята на чисто виртуалните функции е да задължи наследниците да имплементират функцията. В случай, че наследник не имплементира функцията, то той също става абстрактен клас.

## Ключовата дума final
Ключовата дума `final` се използва когато:
* Не искаме наследниците да могат да override-ват виртуална функция.
* Не искаме клас да може да бъде наследяван повече.

```cpp
struct Base
{
    virtual void foo();
};
 
struct A : Base
{
    void foo() final; // Base::foo is overridden and A::foo is the final override
};
 
struct B final : A // struct B is final
{
    void foo() override; // Error: foo cannot be overridden as it is final in A
};
 
struct C : B {}; // Error: B is final
```

## Множествено наследяване
В езикът C++ можем да наследяваме повече от един клас. Синтаксисът е следния:

```cpp
class Derived : <public|private|protected> Base1, <public|private|protected> Base2, ..., <public|private|protected> BaseN;
```

Този подход има както своите предимства така и своите недостатъци. Също така има и неща за които трябва да внимаваме.

## Диамантен проблем.