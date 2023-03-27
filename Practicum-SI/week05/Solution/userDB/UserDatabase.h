#pragma once
#include"../ErrorHandle.h"
#include<cstring>
#include"../User/User.h"

class UserDatabase {
private:
    User users[50];
    size_t size;
public:
    UserDatabase();

    State addUser(const char* name, double balance);

    bool existUser(size_t id) const;

    bool hasEnough(size_t id, double money) const;

    State update(size_t id, double money);

    // Debug
    void printAllUsers() const;
};