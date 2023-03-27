#include"UserDatabase.h"

// Maybe not the best ways to generate indexes,
// but we well find more as the course goes.
namespace IDBuffer {
    size_t userIndex = 0;
}

UserDatabase::UserDatabase() : size{0} {}

State UserDatabase::addUser(const char* name, double balance) {
    if(size == 50)
        return State::UserFull;
    
    users[size++] = User(++IDBuffer::userIndex, name, balance);
    return State::OK;
}

bool UserDatabase::existUser(size_t id) const {
    for (size_t i = 0; i < size; i++)
        if(users[i].getID() == id)
            return true;
    
    return false;
}

bool UserDatabase::hasEnough(size_t id, double money) const {
    for (size_t i = 0; i < size; i++)
        if(users[i].getID() == id)
            return users[i].hasMoney(money);
    
    return false;
}

State UserDatabase::update(size_t id, double money) {
    for (size_t i = 0; i < size; i++)
        if(users[i].getID() == id)
            return users[i].updateMoney(money);

    return State::UserNotFound;        
}

void UserDatabase::printAllUsers() const {
    for (size_t i = 0; i < size; i++)
        users[i].print();
}