# Практикум 25.05.2023

## Задача първа
Реализирайте темплейтна функция `sort`. Ако темплейтния аргумент са числа от тип `unsigned` числата се сортират чрез алгоритъма `counting sort` В противен случай използваме алгоритъма `selection sort`.

Псевдо код на алгоритъма `counting sort`:
```
counting sort(A[0...n]):
    k = max(A)

    count[0...k]
    result[0...n]

    for(i = 0; i <= k; i++):
        count[i] = 0

    for(i = 0; i < n; i++):
        count[A[i]]++
    
    for(i = 1; i <= k; i++):
        count[i] += count[i-1]
    
    for(i = n - 1; i >= 0; i--):
        result[count[A[i]]] = A[i]
        count[A[i]]--
    
    return result
```

## Задача втора
Да се модифицира класът [`SharedPtr`](https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2012/Templates/SharedPtr/SharedPtr.hpp) така, че да приема два аргумента - типът, към който сочи указателя и максималния брой допустими референции.

Пример:

```cpp
SharedPtr<int, 2> ptr(new int(2)); // ok, 1 instance
SharedPtr<int, 2> prt2 = ptr;      // ok, 2 instances
SharedPtr<int, 2> ptr3 = ptr2;     // runtime error/exception
```

## Задача трета
