#pragma once
#include"../ErrorHandle.h"
#include<cstring>  // strlen, strcpy
#include<iostream> // std::cout
#pragma warning (disable : 4996)

class User {
private:
    size_t id;
    char name[32];
    double balance;    
public:
    User();
    User(size_t idArg, const char* nameArg, double balanceArg);
    
    State updateMoney(double factor);
    bool hasMoney(double arg) const;
    size_t getID() const ;

    // Debug
    void print() const;
};