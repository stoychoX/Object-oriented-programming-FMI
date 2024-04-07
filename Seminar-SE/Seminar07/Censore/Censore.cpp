#include "Censore.h"

Censore::Censore(bool (*pred)(char), std::ostream& out) : pred(pred), os(out) {}

Censore& operator<<(Censore& c, const char* str)
{
    while (*str)
    {
        if(c.pred(*str))
        {
            c.os << '*';
        }
        else
        {
            c.os << *str;
        }
        ++str;
    }
    return c;
}
