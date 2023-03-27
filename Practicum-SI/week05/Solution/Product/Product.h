#pragma once
#include"../ErrorHandle.h"
#include<cstring>    // strcpy, strlen
#include<cmath>      // std::abs
#include<iostream>   // std::cout

#pragma warning (disable : 4996)

class Product {
private:
    char name[32];
    size_t ownerId;
    size_t productId;
    size_t quantity;

public:
    Product();

    Product(const char* nameArg, size_t pid, size_t oid, size_t q);

    size_t getQuantity() const;

    State changeQuantity(int amount);

    size_t getProductID() const;

    size_t getOwnerID() const;

    const char* getName() const;

    // Debug
    void print() const;
};