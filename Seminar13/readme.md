# Тринадесети семинар по обектно ориентирано програмиране - 29.05.2025

## Наследяване и влагане на шаблони.
Нека разгледаме следния пример

```cpp
template <class T>
struct Entity
{
    T t;

    const T& get() const 
    {
        return t;
    }
};
```
Нека сега си представим, че искаме да наследим структурата `Entity`. Това може да се случи по два начина.

### Няследяване чрез указване на конктерен тип.
Можем да наследим класът като му дадем конкретен тип. Все пак шаблонът е шаблон, той не е клас. От друга страна `Entity<int>` е напълно валиден клас, който може да бъде наследен.

```cpp
struct IntegerEntity : Entity<int>
{

};

int main()
{
    IntegerEntity e{1};
    std::cout << e.get();
}
```

### Наследяване чрез повторно задаване на шаблона
Можем да не искаме да даваме конкретна стойност на шаблона а да оставим потребителите на наследника да избират кой да е типа на базовия клас. Следния синтаксис е невалиден:

```cpp
class DerivedEntity : public Entity
```
 
Отново - поради причината, че `Entity` сам по себе си не е клас. Можем да позволим на наследника да задава типа на бащата по следния начин:

```cpp
template<class T>
struct DerivedEntity : Entity<T>
{

};

int main()
{
    DerivedEntity<int> e{1};
    std::cout << e.get();
}
```

## Композиция на шаблонни класове.
Подобна е и ситуацията при композиция на шаблонни класове. Можем да ги използваме като член-данни на други класове с конкретен тип или да използваме шаблон, подаден на композиращия клас.

```cpp
struct Compose
{
    Entity<int> e;
};

template<class T>
struct TCompose
{
    Entity<T> e;
};
```

## Пресмятане на стойности по време на компилация (допълнително).

```cpp
template<size_t n>
struct LogDown
{
    static const size_t value = LogDown<n / 2>::value + 1;
};

template<>
struct LogDown<1>
{
    static const size_t value = 0;
};
```

```cpp
template<size_t n>
struct Fibonacci
{
    static const size_t value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
};

template<>
struct Fibonacci<0>
{
    static const size_t value = 0;
};

template<>
struct Fibonacci<1>
{
    static const size_t value = 1;
};
```

```cpp
template<size_t a, size_t b>
struct GCD
{
    static const size_t value = GCD<b, a % b>::value;
};

template<size_t a>
struct GCD<a, 0>
{
    static const size_t value = a;
};
```


## Указатели към функции. Функции от по - висок ред. Обекти, държащи се като функции. lambda функции и начина им на имплементация.

## Задача първа
Да се реализира клас `IntFunctionAverage`, който използва две функции (или обекти, държащи се като такива) и за число x връща `f1(x) + f2(x) / 2`. Да се използва класа в пример, в който едната функция е идентитета, а другата е идентитета ако числото се съдържа във подаден файл и 0 в противен случай.