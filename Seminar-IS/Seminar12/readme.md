# Дванадесети семинар по обектно ориентирано програмиране - ИС

# Хетерогенни контейнери
Можем да реализираме колекция (контейнер) от обекти от различни типове (но с общ базов клас). Указателите трябва да са от типа на базовия клас. При примера с фигурите (Shapes) видяхме следния пример:
```cpp
Shape **arr = new Shape *[4];

arr[0] = new Rectangle(3, 4, 6, 8);
arr[1] = new Circle(3, 3, 4);
arr[2] = new Circle(1, 4, 5);
arr[3] = new Triangle(1, 1, 2, 2, 3, 3);
```

В случая това е някаква колекция от различни типове. Можем да обвием тази идея в клас капсулирайки логиката за хетерогенен контейнер.

Пример:
```cpp
struct Fruit
{
	virtual void printColor() const = 0;
	virtual ~Fruit() = default;
};

struct Apple : public Fruit
{
	void printColor() const override
	{
		std::cout << "Red or green! "<<std::endl;
	}
};

struct Orange : public Fruit
{
	void printColor() const override
	{
		std::cout << "Orange! "<<std::endl;
	}
};

struct Lemon : public Fruit
{
	Lemon(size_t sourness) : sourness(sourness){}
	
	size_t sourness;
	void printColor() const override
	{
		std::cout << "Yellow! "<<std::endl;
	}
};

class FruitStore
{
private:
	Fruit** fruits;
	size_t capacity;
	size_t count;
          
    void copyFrom(const FruitStore& other);
    void free();
    
public:
	FruitStore();
	FruitStore(const FruitStore&);
	FruitStore& operator=(const FruitStore&);
    ~FruitStore();
	
	void addApple();
    void addOrange();
    void addLemon(size_t sourness);
};

void FruitStore::addApple()
{
	fruits[count++] = new Apple();
}

void FruitStore::addOrange()
{
	fruits[count++] = new Orange();
}
void FruitStore::addLemon(size_t sourness)
{
	fruits[count++] = new Lemon(sourness);
}
```

## Триене
Понеже деструктора е виртуален не се интересуваме от типа на обектите, които трием, и разчитаме, че деструкторите са дефинирани коректно. Това е един от случаите, които **ке възползват от виртуалния деструктор.**
```cpp
void FruitStore::free()
{
	for(int i = 0; i < count; i++)
		delete fruits[i];
	delete[] fruits;
}
```

## Копиране
Искаме да реализираме копиране на колекцията. Това трябва да стане без да нарушаваме абстракцията - искаме обеките да се копират без да се налага да запитваме за техния тип. За това дефинираме виртуална функция clone, която ще връща копие на обекта. Тази функция я разписваме във всеки от наследниците.

```cpp

struct Fruit
{
	virtual void printColor() const = 0;
	virtual ~Fruit(){}

    virtual Fruit* clone() const = 0; //!
};

struct Apple : public Fruit
{
	void printColor() const override
	{
		std::cout << "Red or green! "<<std::endl;
	}
	Fruit* clone() const override
	{
		return new Apple(*this);
    }
};

struct Orange : public Fruit
{
	void printColor() const override
	{
		std::cout << "Orange! "<<std::endl;
	}
	
	Fruit* clone() const override
	{
		return new Orange(*this);
	}
};

struct Lemon : public Fruit
{
	Lemon(size_t sourness) : sourness(sourness){}
	
	size_t sourness;
	void printColor() const override
	{
		std::cout << "Yellow! "<<std::endl;
	}
	Fruit* clone() const override
	{
		return new Lemon(*this);
    }
};
```

От тук копирането става тривиално:

```cpp
void FruitStore::copyFrom(const FruitStore& other)
{
	fruits = new Fruit*[other. capacity];
	for(int i = 0; i < other.count; i++)
		fruits[i] = other.fruits[i]->clone();
	count = other.count;
	capacity = other.capacity;
}
```

## Пример първи
Да се реализира следната полиморфна йерархия:
* Animal - абстрактен клас, описващ животно. То има единствена чисто виртуална функция `makeNoice`. Всяко животно пази информация за типа си.
* Наследници Cat, Dog и Cow.
* Клас ферма (farm) - колекция от животни. Тя поддържа:
  * addAnimal(animalType) - добавя животно по тип. Помислете как ще се реализира тази функция. Чия отговорност е да определи коя животно се добавя спрямо подадения тип??
  * makeNoiceAll - извиква базовата функция на всички наследници
  * getTypeByIndex(index) - провирява типа на животното на подаден индекс.

## Шаблони
Функция/клас, която работи не с променливи от някакъв дефиниран тип, а с абстрактни променливи, се нарича шаблонна функция/клас

### Шаблонни функции
Нека разгледаме следния пример:
```cpp
int add(int a, int b) { return a + b; }
float add(float a, float b) { return a + b; }
double add(double a, double b) { return a + b; }
```
Това е валиден код. Забелязваме, че имаме повторение - единственото нещо по което тези три функции се различават е типа, който приемат. Възможно ли е да напишем дефиницияна на функцията `add` само веднъж? Използвайки шаблони е възможно.
```cpp
template<class T>
T add(const T& a, const T& b) { return a + b; }
```
В случая `add` ще работи за всеки тип поддържащ `operator+`:
```cpp
#include <iostream>

template<class T>
T add(const T& a, const T& b) { return a + b; }

int main() {
	std::cout << add<int>(1, 2) << " " << add<float>(1.5f, 1.7f) << " " << add<std::string>("Hello, ", "world");
}
```

Защо пускаме аргументите като константни референции?
Компилатора може автоматично да определи типа на аргументите (ако той е известен по време на компилация)
```cpp
template<class T>
T add(const T& a, const T& b) { return a + b; }

int main() {
	std::cout << add(1, 2) << " " << add(1.5f, 1.7f) << " " << add("Hello, ", "world");
}
```
Ако направим нещо такова ще получим грешка. При първото и второто извикване всичко е ок - компилатора разбира, че става въпрост за `int` и `float`. При третото извикване обаче компилатора познава подадените типове като `const char[]` а не като `std::string`. Знаем, че не можем да конкатенираме променливи от тип `const char[]` използвайки `opeartor+` и компилатора ни дава грешка.

```cpp
template<class T>
T add(const T& a, const T& b) { return a + b; }

int main() {
	std::cout << add(1, 2) << " " << add(1.5f, 1.7f) << " " << add<std::string>("Hello, ", "world");
}
```

### Шаблонни класове
Можем да приложим същата техника при класовете.

```cpp
template<class T>
class Exmaple {
	T t;
public:
	Exmaple(const T& t_) : t(t_) {}

	T next() {
		return t++;
	}
};

int main() {
	Exmaple<int> e_int(1);
	int arr[] = { 5, 6, 7, 8 };
	Exmaple<int*> e_int_ptr(arr);

	for (size_t i = 0; i < 4; i++) {
		std::cout << e_int.next() << " ";
	}

	std::cout << std::endl;

	for (size_t i = 0; i < 4; i++) {
		std::cout << *e_int_ptr.next() << " ";
	}
}
```
В случая можем да изградим `Example` с всеки тип, който поддържа `operator++`.

Можем да имаме повече от един шаблонни аргумента:
```cpp

template<class T, class U>
struct pair
{
	T first;
	U second;
};

template<class T, class U>
pair<T, U> make_pair(const T& t, const U& u)
{
	return { t, u };
}

int main()
{
	pair<int, double> p = make_pair(1, 2.0);
	std::cout << p.first << " " << p.second;
}
```

Не е нужно да използваме единствено типа - можем да имаме масиви, указатели и т.н. от него както с всеки нормален тип:

```cpp
template<class T>
class optional
{
private:
    T* opt; // Можем да имаме указатели към Т.
//....
};
```

### Нетипови прараметри
Можем да пуснем определен тип в списъка на `templаte`
```cpp

template<class T, unsigned size>
class myArray
{
private:
	T arr[size];
public:
	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

	size_t get_size() const
	{
		return size;
	}
};

template<class T, unsigned size>
T& myArray<T, size>::operator[](size_t idx)
{
	return arr[idx];
}

template<class T, unsigned size>
const T& myArray<T, size>::operator[](size_t idx) const
{
	return arr[idx];
}


int main()
{
	// Using standard arrays:
	int arr[10];
	for (size_t i = 0; i < 10; i++)
	{
		arr[i] = i;
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;

	// using my array:
	myArray <int, 10> m_arr;
	for (size_t i = 0; i < 10; i++)
	{
		m_arr[i] = i;
		std::cout << m_arr[i] << " ";
	}
}
```

### Специализации
Можем да окажем специално поведение на клас от даден тип.

```cpp
#include <iostream>

template<class T>
struct Example
{
	void f()
	{
		std::cout << "This is boring exmaple..." << std::endl;
	}
};

template<> struct Example<int>
{
	void f()
	{
		std::cout << "This is int exmaple..." << std::endl;
	}
};


template<> struct Example<char>
{
	void f()
	{
		std::cout << "This is char exmaple..." << std::endl;
	}
};

int main()
{
	Example<int> e_int;
	Example<char> e_char;
	Example<double> e_double;

	e_int.f();
	e_char.f();
	e_double.f();
}
```

### Начин на работа на шаблоните. Възможни компилационни грешки при работа с шаблони.
Нека се опитаме да разделим шаблонен клас на `.h` и `.cpp` файлове.

```cpp
// Example.h
#pragma once

template<class T>
class Example
{
public:
	T get();
};
```
```cpp
// Example.cpp
#include "Exmaple.h"

template<class T>
T Exmaple<T>::get()
{
	return T();
}
```
```cpp
// src.cpp
#include <iostream>
#include "Example.h"
int main()
{
	Example<int> e;
	std::cout << e.get();
}
```
Този код завършва с грешка при свързването (Linking error). Грешката ни казва, че не можем да намерим символа `int Exmaple<int>::get()`.
Но зашо се случва това? В случая имаме две единици, които се опитваме да компилираме - `src.cpp` и `Example.cpp`. И двете са синтактично правилни, следователно се компилират правилно. Използвайки шаблони компилатора намира всички места на които извикваме шаблона с конкретен тип и изглежда версия на класа или функцията с конкретния тип. Ако има някакви типови изисквания, които не са изпълнени (примерно типа не поддържа някой оператор) това завършва като компилационна грешка.

В случая обещаваме на `src.cpp`, че някъде съществува `int Exmaple<int>::get()`. Това обаче не е така - в `Example.cpp` никъде не изграждаме търсената функция понеже никъде не я викаме. Едно решение е да я изградим собственоръчно. 

```cpp
// Example.cpp
#include "Exmaple.h"

template<class T>
T Exmaple<T>::get()
{
	return T();
}
```

```cpp
// Example.cpp
#include "Exmaple.h"

template<class T>
T Exmaple<T>::get()
{
	return T();
}

template int Example<int>::get();
```
Сега вече нямаме проблеми. Но ако ни се наложи да използваме функцията с друг тип, примерно `char` ще трябва да добавим същото само, че за `char` типа.

Втория начин, който не ни задължава да казваме експлицитно кои типове ползваме, е да използваме `.hpp` файлове. 
```cpp
// Example.hpp
#pragma once

template<class T>
class Example
{
public:
	T get();
};

template<class T>
T Exmaple<T>::get()
{
	return T();
}
```

```cpp
// src.cpp
#include <iostream>
#include "Example.hpp"

int main()
{
	Example<int> e;
	std::cout << e.get();
}
```
Сега, компилирайки `src.cpp`, ще имаме и дефинициите и декларациите на шаблонните функции във файла (след като се изпълни препроцесора). Благодарение на това ще намерим нужните символи и няма да има нужда да ги пишем експлицитно. И двата метода се използват в зависимост от ситуацията (но `.hpp` файловете са предпочитани в повечето случаи).

## Задача първа
Стек наричаме абстрактна структура от данни поддържаща следния интерфейс:
```
push(arg) - добавя елемент.
pop() - премахва елемент.
top() - връща последния добавен елемент.
```
Да се реализира клас `FiniteStack`, който реализира абстрактната структура от данни стек. Тя има краен размер (подаден от потребителя).

```cpp
int main()
{
    FiniteStack<int, 10> s;

    s.push(1);
    s.push(2);
    s.push(3);

    std::cout << s.top(); // 3
    s.pop();
    std::cout << s.top(); // 2
}
```
