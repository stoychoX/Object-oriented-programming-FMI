## Бонус тема - ламбда изрази и функции от по-висок ред.
Функция от по-висок ред наричаме функция, която изпълнява едно от следните изисквания:
* Приема една или повече функции като аргумент.
* Връща функция като резултат.

Подаването на функции е особено удобно в някои ситуации. Примерно, искаме да търсим елемент в колекция. Може да искаме да търсим първия елемент, който се дели на две. Но може да искаме да търсим първия, който се дели на пет. Може да искаме да търсим първото просто число и тн. Ако за всяко такова наше изискване ни се налага да пишем по една функция, то това би било дублиране на код. 

Функции можем да подаваме като аргументи към други функции като използваме указатели към тях.
Примерно
```cpp
bool (*isEven)(int);
```
е указател към функция, която връща `bool` и приема един аргумент от тип `int`. 

```cpp
T (*functionName)(T1 arg1, T2 arg2...);
```
Нека разгледаме как можем да напишем функцията `find_if` която претърсва масив и връща позицията на първия елемент, който отговаря на предикат. Ако такъв елемент не съществува нека функцията да връща -1.

```cpp
int find_if(const int* arr, size_t size, bool (*pred)(int))
{
    for(size_t i = 0; i < size; i++)
    {
        if(pred(arr[i]))
            return i;
    }
    return -1;
}
```
В скоупа на функцията, която като аргумент приема функция, използваме подадената функция като всяка друга. Единственото, което може да е леко объркващо, е синтаксисът на указателя към функция.
Нека видим как можем да извикаме функцията:

```cpp
#include <iostream>

bool isEven(int x)
{
    return (x % 2 == 0);
}

bool isBiggerThanThree(int x)
{
    return x > 3;
}

int find_if(const int* arr, size_t size, bool (*pred)(int))
{
    for (size_t i = 0; i < size; i++)
    {
        if (pred(arr[i]))
            return i;
    }
    return -1;
}

int main()
{
    int example[4] = { 1, 2, 3, 4 };

    int evenIdx = find_if(example, 4, isEven);
    int biggerThanThreeExample = find_if(example, 4, isBiggerThanThree);

    std::cout << example[evenIdx] << " " << example[biggerThanThreeExample];
}
```

Това ще отпечата първото четно число и първото число по - голямо от 3.

Можем и още да съкратим синтаксиса.
```cpp
#include <iostream>

int find_if(const int* arr, size_t size, bool (*pred)(int))
{
    for (size_t i = 0; i < size; i++)
    {
        if (pred(arr[i]))
            return i;
    }
    return -1;
}

int main()
{
    int example[4] = { 1, 2, 3, 4 };

    int evenIdx = find_if(example, 4, [](int x) -> bool { return x % 2 == 0; });

    int biggerThanThreeExample = find_if(example, 4, [](int x) -> bool { return x > 3; });

    std::cout << example[evenIdx] << " " << example[biggerThanThreeExample];
}
```
Това, което подадохме като трети аргумент на `find_if`, е анонимен ламбда израз. Той, както можем да се досетим, представлява функция, която връща bool и приема като аргумент число x.

```
[](Аргументи, които функцията приема) -> Tип на връщане { Тяло на функцията };
```
В първите скоби на израза (т.нар. capture) се подават аргументи от скоупа, които може да искаме да използваме в тялото на функцията. Тях може да разгледаме по-късно в курса.