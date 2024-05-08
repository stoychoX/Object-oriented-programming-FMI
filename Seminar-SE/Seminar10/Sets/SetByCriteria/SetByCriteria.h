#pragma once
#include "../DynamicSet/DynamicSet.h"

class SetByCriteria : private DynamicSet
{
public:
    SetByCriteria(unsigned n, bool (*incl)(unsigned n));
    void setInclude(bool (*incl)(unsigned n));

    // Syntax is alternative to making our public verion of
    // print and calling DynamicSet::print() in it.
    using DynamicSet::print;
    using DynamicSet::contains;

private:
    void fillSet(bool (*criteria)(unsigned n));
};
