#include"User.h"

User::User() : id{0}, name{""}, balance{0}{}

User::User(size_t idArg, const char* nameArg, double balanceArg) : id{idArg}, balance{balanceArg}, name{""} {
    if(strlen(nameArg) < 32)
        strcpy(name, nameArg);
}

State User::updateMoney(double factor) {
    if(balance + factor < 0)
        return State::NegativeBalance;
    
    balance += factor;
    return State::OK;
}

bool User::hasMoney(double arg) const {
    return balance > arg;
}

size_t User::getID() const {
    return id;
}

void User::print() const {
    std::cout << "Name: " << name << std::endl <<
        "User ID: " << id << std::endl <<
        "Balance: " << balance << std::endl << std::endl;
}