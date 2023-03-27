#pragma once
#include"../ErrorHandle.h"
#include<cmath> // std::abs, size_t
#include<iostream> // std::cout

class Price {
private:
    size_t productId;
    double price;

public:
    Price();

    Price(size_t id, double p);
    
    size_t getId() const;

    double getPrice() const;

    State updatePrice(double amount);

    // Debug:
    void print() const;
};