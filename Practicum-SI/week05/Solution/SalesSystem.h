#pragma once
#include"userDB/UserDatabase.h"
#include"productDB/ProductDatabase.h"
#include"priceDB/PricesList.h"

class SalesSystem {
private:
    UserDatabase users;
    ProductDatabase products;
    PricesList prices;

public:
    SalesSystem();

    State addUser(const char* name, double balance);

    State addProduct(const char* name, size_t ownerID, size_t quantity);

    State addPrice(size_t productID, double price);

    State sell(size_t idFrom, size_t idTo, size_t productID, size_t quantity);

    // Debug
    void print(const char* msg) const;
};