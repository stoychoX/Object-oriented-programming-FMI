#include <iostream>

class Censore
{
private:
    std::ostream& os;
    bool (*pred)(char);
public:
    Censore(bool (*pred)(char), std::ostream&);

    friend Censore& operator<<(Censore& c, const char* str);
};
