# Практикум 18.05.2023

## Задача първа
Да се реализира клас `array<T, size_t>`, който представя статичен масив. Класът трябва да поддържа следния интерфейс:

```cpp
array<int, 10> a1;

std::cout << a1.size() << " " << a1.empty();

a1.fill(10);

for (size_t i = 0; i < 10; i++)
    assert(a1[i] == 10);
```

## Задача втора
Да се реализира клас `vector<T>`. Класът трябва да поддържа следния интерфейс:

* `vector<T>()` - конструктор по подразбиране (size = 0, capacity = 8)
* `vector<T>(size_t n)` - size = n, capacity = n
* `vector<T>(size_t n, const T& elem)` - size_t = n, capacity = n, всеки елемент има стойност elem
* `push_back` - добавя елемент в края
* `pop_back()` - премахва последния елемент
* `operator[](size_t at)` - достъпва елемент на позиция
* `empty()`
* `size()`
* `capacity()`
* `clear()` - премахва всички елементи. size = 0, capacity остава непроменено. 