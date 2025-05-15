# Десети семинар по обектно ориентирано програмиране - ИС

## Наследяване
С течение на курса се запознахме с понятията композиция и агрегация. Общото между тези две понятия беше, че даден клас (по един или друг начин) притежава (или използва) друг. 

```cpp
class EventLogger;

class Event
{
private:
    EventLogger& logger;

public:
    void execute()
    {
        // ...
        logger.log("Event executed...");
        // ...
    }
};
```

Тези подходи ни помагат да изградим по-добра архитектура на нашия код и да спестим писането му. Вместо във всеки един клас, използващ някаква логика, да разписваме желаната функционалност я изнасяме в отделен клас, който използваме като част от други класове, преизползващи логиката.

Такива връзки още не наричат `has-a relationship`. В примера класовете `Event` и `EventLogger` са в `has-a relationship`.

Нека си представим, че правим йерархия, която се занимава с различни типове събития. Събитието, започва и завършва в даден момент. Също така можем да имаме и събитие, което е предназначено само за определена група от хора. Как бихме реализирали тази йерархия използвайти `has-a` връзки?

```cpp
class Event
{
    Timestamp from;
    Timestamo to;

    Group targetGroup;
};
```

Това е една примерна (не особено добра) имплементация. В случая, ако `Event` е събитие, насочено към определена група хора, в член-данната `targetGroup` ще бъде записана конкретната група. В противен случай, ако е нормално събитие, тя ще бъде оставена празна. Какъв може да е проблемът тук?

1. В общия случай пазим променлива, която не използваме - не винаги targetGroup ще бъде използвана.
2. Нямаме ясно разделение между обикновените събития и събитията, предназначени за групи. 
    - Описвайки архитектурата казахме, че има два типа събития. Как знаем дали обекта, с който работим, е обикновено събитие, или събитие за група от хора, което няма да бъде посетено?
3. Йерархията е трудна за разширяване
    - Ако в последствие се наложи да се добави нов вид събитие, то това би довело до разширяване на класа Event с още една (потенциално празна) член данна.

Проблемът тук е, че се опитваме да представим два обекта с един. В случая имаме обектите `Event` и `SpecificAudienceEvent`. Опитвайки се да спестим код единствено усложнихме архитектурата. Нека разделим обектите:

```cpp
class Event
{
    Timestamp from;
    Timestamp to;
};

class SpecificAudienceEvent
{
    Timestamp from;
    Timestamp to;

    Group targetGroup;
};
```
Тук вече имаме разделение на обектите. В случая `SpecificAudienceEvent` също в някакъв смисъл е `Event`, но по - специфичен. Проблемът тук е, че при промяна на `Еvent` ще трябва да променим и `SpecificAudienceEvent`.

Можем и да подходим чрез `has-a` връзка, но дали това е коректно на идейно ниво? Събитието за специфична публика има ли в себе си събитие или е събитие?

Втория тип връзки, който ще разгледаме, са така наречените `is-a relationship`. При тях единия обект не притежава другия, а по - скоро го разширява.

Наследяването е метод за реализиране на `is-a` връзки. Чрез него създаваме нови класове от съществуващи (механизъм за повторно използване). Новия клас съдържа данни и поведение на съществуващия клас. 

```cpp
class Event
{
    Timestamp from;
    Timestamp to;
public:
    bool intersect(const Event& other) const;
};

class SpecificAudienceEvent : public Event
{
    Group targetGroup;
public:
    bool hasMutualAttendants(const SpecificAudienceEvent& other) const;
};

int main()
{
    Event e1;
    Event e2;

    e1.intersect(e2);

    SpecificAudienceEvent se1;
    SpecificAudienceEvent se2;

    // We can call methods from the base class.
    se1.intersect(e1);
    se1.intersect(se2);

    se2.hasMutualAttendants(se1);
}
```

## Видове наследяване
Можем да наследим клас по един от следните три начина:
```cpp
class Der1 : public Entity{};
class Der2 : protected Entity{};
class Der3 : private Entity{};
```

* При класовете наследяването е private по подразбиране.
* Можем да наследяваме и структури. При тях наследяването е public по подразбиране. 
* Тези три начина определят каква част от член-данните на бащата ще е видима за наследниците.

## Ключовата дума protected.
* При класовете по подразбиране член-данните са `private`. 
* При структурите пък те са публични за външния свят. 
* Въвеждайки концепцията за наследяване би било логично да си зададем въпросът каква част от член-данните на родителя биха били видими за наследника.

Можем да искаме, за определена член-данна, тя да е видима в наследниците, но да не е видима за външния свят. Точно от тук идва и нуждата от protected.

Член-данните декларирани като protected могат да се достъпват в наследниците, но не и от външния свят.

![](media/table-class.png)

```cpp
class A  {
public:
    int x;
protected:
	int y;
private:
    int z;
};

class B : public A {
    // x is public
    // y is protected
    // z is not accessible from B
};

class C : protected A {
    // x is protected
    // y is protected
    // z is not accessible from C
};

class D : private A { // 'private' is default for classes
    // x is private
    // y is private
    // z is not accessible from D
};
```

## Подаване като параметри на функции
Класове-наследници могат да бъдат подавани като параметри на функции, които приемат обекти от базовия клас.
Може да се използва функционалността само от базовия клас.
```cpp
#include <iostream>

class Entity
{
public:
	void f()
	{
		std::cout << "Entity::f()" << std::endl;
	}
};

class Der : public Entity
{
public:
	void g()
	{
		std::cout << "Der::g()" << std::endl;
	}
};

void f(Entity* e)
{
	e->f();
}

void g(Entity& e)
{
	e.f();
}

void h(Entity e)
{
	e.f();
}

void k(Der d)
{
	d.g();
}

int main()
{
	Der d;
	f(&d);
	g(d);
	h(d);

	Entity e;
	k(e); // Not ok.....
}
```

## Конструктори и деструктори при наследяване
* Когато **Derived** класът наследява **Base**, то **Base** трябва да бъде инициализиран преди **Derived**.
* Когато се създава наследник първо се вика конструктора на бащата и след това се разписва този на наследника.

* Деструкторите се извикват в обратен ред на конструкторите.

Във всеки контструктор на класът-наследник, трябва да се оказва кой конструктор да се извика за базовия клас.
Ако не оказано, ще се извика конструктора по подразбиране.

Деструкторът на наследния клас извиква деструктора на базовия клас.

## Копиране при наследяване
При разписване на конструктора за копиране и оператора за присовяване на клас-наследник, трябва експлицитно да извикваме копиране и за базовия клас.

```cpp
B::B(const B& other) : A(other) { // copy constructor of A (base class)
   copyFrom(other);
}

B& B::operator=(const B& other) {
   if (this != &other) {
   	A::operator=(other); //operator= of A (base class)
   	free();
   	copyFrom(other);
   }
   return *this;
}
```
* Ако НЕ ги дефинирате в Derived класа, компилаторът ще ги създаде автоматично и ще извика версията на базовия клас.
* Ако ги дефинираме в Derived класа, трябва изрично да се извикат базовите(invoke the Base class definition explicitly)

## Move semantics
```cpp
class MyString {
private:
	char* str;
public:
	//... constructors
	MyString(MyString&& rhs) : str(rhs.str) {
		rhs.str = nullptr;
	}

	MyString& operator=(MyString&& rhs) {
		if (this != &rhs) { 
		    delete[] this->str;  //deallocate storage for this->str since we are overwriting it
		    str = rhs.str;		 //steal the pointer from the rhs object and assign it to this->str
		    rhs.str = nullptr;   //null out the rhs pointer
        	}
		return *this;		 //return the current object by reference to allow chain assignment
	}
};

class Text : public MyString {
private:
	char* biggerStr;
public:
	//consturctors
	Text(Text&& rhs) : MyString(std::move(rhs)), biggerStr(rhs.biggerStr) {
		rhs.biggerStr = nullptr;
	}
	
	Text& operator=(Text&& rhs) {
		if (this != &rhs) {
			MyString::operator=(std::move(rhs));
			delete[] biggerStr;
			biggerStr = rhs.biggerStr;
			rhs.biggerStr = nullptr;
		}
		return *this;
	}
};
```

## Задача първа
Да се реализира следната йерархия:
1. Базов клас `Person`. Той има име с произволна дължина и възраст.
2. Клас `Student`. Той разполага с факултетен номер.
3. Клас `Teacher`. Той пази в себе си какви предмети води. Предметите се подават в конструктора и не могат да бъдат модифицирани.