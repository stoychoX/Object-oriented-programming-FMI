#pragma once
#include"../ErrorHandle.h"
#include"../Price/Price.h"

class PricesList {
private:
    Price prices[50];
    size_t size;
public:
    PricesList();

    State addPrice(size_t itemID, double price);

    double getPrice(size_t id) const;

    // Debug:
    void print() const;
};