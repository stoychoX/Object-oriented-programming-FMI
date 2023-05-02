#include<cassert>
#include<iostream>
#include"Student-with-move.h"
#include"unique_ptr.h"

int main() {
    {
        Student s("Mr Mover", nullptr, 0);

        Student s2(std::move(s));

        assert(s.getName() == nullptr && s2.getName() != nullptr);

        s = std::move(s2);

        assert(s.getName() != nullptr && s2.getName() == nullptr);
    }

    {
        unique_pointer u(new int);
        *u = 10;

        // unique_pointer u1 = u; -- error
        // try passing u to a function
        std::cout << *u << std::endl;
        // No leaks -- destructor is called here!
    }
}