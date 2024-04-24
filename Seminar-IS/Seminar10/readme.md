# Десети семинар по обектно ориентирано програмиране - ИС

## Наследяване
С течение на курса се запознахме с понятията композиция и агрегация. Общото между тези две понятия беше, че даден клас (по един или друг начин) притежава (или използва) друг. 

```cpp
class EventLogger;

class Event
{
private:
    EventLogger& logger;
};
```

Тези подходи ни помагат да изградим по-добра архитектура на нашия код и да спестим писането на код. Вместо във всеки един клас, използващ някаква логика, да разписваме дадена функционалност я изнасяме в отделен клас, който по един или друг начин ни помага в последствие.

Такива връзки още не наричат `has-a relationship`. В примера класовете `Event` и `EventLogger` са в `has-a relationship`.

Нека си представим обаче, че правим някаква йерархия, която се занимава с различни типове събития. Можем да имаме събитие, което започва и завършва в даден момент. Също така обаче можем да имаме и събитие, което е предназначено само за определена група от хора. Как бихме реализирали тази йерархия използвайти `has-a` взаимоотношения?

```cpp
class Event
{
    Timestamp from;
    Timestamo to;

    Group targetGroup;
};
```

Това е една примерна (не особено добра) имплементация. В случая, ако `Event` е събитие насочено към определена група хора в член-данната `targetGroup` ще бъде записана конкретната група. В противен случай, ако е нормално събитие, тя ще бъде оставена празна. Какъв е проблемът тук?

От програмистка гледна точка е ненужно да пазим променлива, която не използваме. Разбира се, тя може да няма голям размер, но ако това стане практика не би ни отвело на добри места.

От гледна точка на отношенията между обектите този подход също не е правилен. Грешката тук е, че се опитваме да представим два обекта с един. В случая имаме обектите `Event` и `SpecificAudienceEvent`. Опитвайки се да спестим код единствено усложнихме архитектурата. Нека разделим обектите:

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
Това е малко по - поносимо, но отново можем да се справим добре. В случая `SpecificAudienceEvent` също в някакъв смисъл е `Event`, но по - специфичен. Можем да кажаме, че при тях връзката е `is-a`.

Наследяването е метод за реализиране на подобни `is-a` връзки. Чрез него създаваме нови класове от съществуващи (механизъм за повторно използване). Новия клас съдържа данни и поведение на съществуващия клас. 

```cpp
class Event
{
    Timestamp from;
    Timestamp to;
};

class SpecificAudienceEvent : public Event
{
    Group targetGroup;
};
```

## Видове наследяване
Можем да наследим клас по един от следните три начина:
```cpp
class Der1 : public Entity{};
class Der2 : protected Entity{};
class Der3 : private Entity{};
```

При класовете наследяването е private по подразбиране. Тези три начина определят каква част от член-данните на бащата ще е видима за наследниците.

## Ключовата дума protected.
При класовете по подразбиране член-данните бяха `private`. При структурите път те са публични за външния свят. Въвеждайки конципцията за наследяване би било логично да си зададем въпросът каква част от член-данните на родителя биха били видими за наследника.

Можем да искаме за определена член-данна тя да е видима в наследниците, но да не е видима във външния свят. Точно от тук идва и нуждата от protected.

Член-данните декларирани като protected могат да се достъпват в наследниците, но не и от външния свят.

![](media/inheritance.png)

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

Деструкторите се извикват в обратен ред на конструкторите. Първо се извиква деструктора на наследяващия клас и след това този на наследника.

Във всеки контструктор на класът-наследник, трябва да се оказва кой конструктор да се извика за базовия клас.
Ако не оказано, ще се извика конструктора по подразбиране.

Деструкторът на наследния клас извиква деструктора на базовия клас.
## Копиране при наследяване
При разписване на конструктора за копиране и оператора за присовяване на клас-наследник, трябва експлицитно да извикваме копиране и за базовия клас.

```cpp
B::B(const B& other) : A(other) { // (copy constructor of A (base class)
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

## Примери за наследяване

## Задача първа
Да се реализира следната йерархия:
1. Базов клас `Person`. Той има име с произволна дължина и възраст.
2. Клас `Student`. Той разполага с факултетен номер.
3. Клас `Teacher`. Той пази в себе си какви предмети води. Предметите се подават в конструктора и не могат да бъдат модифицирани.