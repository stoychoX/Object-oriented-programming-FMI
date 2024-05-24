#include <iostream>

template <class T, class U>
struct pair
{
    T first;
    U second;

    template <class T, class U>
    friend std::ostream &operator<<(std::ostream &os, const pair<T, U> &p);
};

template <class T, class U>
pair<T, U> make_pair(const T &first, const U &second)
{
    return {first, second};
}

template <class T, class U>
std::ostream &operator<<(std::ostream &os, const pair<T, U> &p)
{
    os << p.first << " " << p.second << std::endl;
    return os;
}