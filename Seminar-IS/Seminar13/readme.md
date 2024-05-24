# Тринадесети семинар по обектно ориентирано програмиране - ИС

## Задача първа
Да се реализира клас `optional<T>`. Класът представлява обект, който може да има стойност, от тип `T`, а може и да няма.
Класът трябва да поддържа следния интерфейс:

* operator*() - Връща стойността.
* has_value() - Казва дали имаме стойност.
* value()     - Връща стойността
* value_or()  - Връща стойността ако има такава в противен случай връща подаден аргумент.
* reset()     - Унищожава стойността ако има такава

## Обекти държащи се като функции
В С++ обект държащ се като функция (функционален обект) е обект, който може да бъде извикан като функция (най - често със същия синтаксис).

```cpp
#include <iostream>

class Adder
{
private:
    int toAdd;
public:
    Adder(int add): toAdd(add) {}

    void operator()(int& x) { x += toAdd; }
};

int main()
{
    int x = 10;
    Adder a(11);

    a(x);
    std::cout << x;
}
```

В примера можем да използваме обекта точно както използваме функция. Можем да се възползваме от тази техника - понякога, за изпълнението на функция, ни е нужен контекст. 
Създавайки обект, който се държи като функция (извиква се като нея), можем да пазим този контект като член данна на обекта.

Нека разгледаме следния прост пример - ще се опитаме да съберем две числа.
```cpp
#include <iostream>

using function = void (*)(int&);

void apply(function functor, int& x)
{
    functor(x);
}

int main()
{
    int first = 0;
    int second = 0;
    std::cout << "Enter first number: ";
    std::cin >> first;
    std::cout << "Enter second number: ";
    std::cin >> second;

    apply([](int& x) -> void { x += second; }, first);
}
```
Това обаче не работи. Защо? `second` не е видима в подадения израз. Това е работата на първите скоби - всяка променлива, която е от външния scope и искаме да е видима в израза се записва там. Да пробваме следното:

```cpp
#include <iostream>

using function = void (*)(int&);

void apply(function functor, int& x)
{
    functor(x);
}

int main()
{
    int first = 0;
    int second = 0;
    std::cout << "Enter first number: ";
    std::cin >> first;
    std::cout << "Enter second number: ";
    std::cin >> second;

    apply([&second](int& x) -> void { x += second; }, first);
}
```

Това обаче също не работи. Защо? Накратко - указателя към функция **не** може да има контекст (какъвто всъщност е second в горния пример). Указателя е указател, няма място за допълнителен контекст. При липса на контекст С++ може да превърне ламбда израза в указател към функция.

Какво правим? 

```cpp
#include <iostream>

class Adder
{
private:
    int toAdd;
public:
    Adder(int add): toAdd(add) {}

    void operator()(int& x) { x += toAdd; }
};

template<class Functor>
void apply(const Functor& functor, int& x)
{
    functor(x);
}

int main()
{
    int first = 0;
    int second = 0;
    std::cout << "Enter first number: ";
    std::cin >> first;
    std::cout << "Enter second number: ";
    std::cin >> second;

    apply([&second](int& x) -> void { x += second; }, first);
}
```

В случая отново ще можем да подадем функция от по-висок ред. Но можем да правим и нещо повече - можем да подадем обект, който се държи като такава. Той вече може да пази нужния ни контекст.

## Пример 
Да се напише клас `FunctionAverage` приемащ две функции (или обекти, които се държат като такива). Класът връща средната стойност на двете функции.

На стандартния вход се подава път към файл. Използвайки този клас да се реализира обект, който връща средното на идентитета и функция следната функция:

f(x) = x ако x се среща във файла.
f(x) = 0 в противен случай.
