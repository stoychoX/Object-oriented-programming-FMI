#pragma once
#include"../ErrorHandle.h"
#include"../Product/Product.h"

class ProductDatabase {
private:
    Product products[50];
    size_t size;
public:
    ProductDatabase();

    State addProduct(const char* name, size_t ownerID, size_t quantity);

    const char* getName(size_t productID) const;

    bool existProduct(size_t id) const;

    size_t itemsOwned(size_t id, size_t productID) const;

    State update(size_t id, size_t productID, int update);

    // If we have product with quantity = 0 we remove it
    void cleanupDatabase();

    bool isFull() const;

    // Debug
    void print() const;
};