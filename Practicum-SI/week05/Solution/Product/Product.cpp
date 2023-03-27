#include"Product.h"

Product::Product() : name {""}, ownerId{0}, productId{0}, quantity{0} {}

Product::Product(const char* nameArg, size_t pid, size_t oid, size_t q) : name{""}, productId{pid}, ownerId{oid}, quantity{q} {
    if(strlen(nameArg) < 32) 
        strcpy(name, nameArg);
}

size_t Product::getQuantity() const {
    return quantity;
}

State Product::changeQuantity(int amount) {
    if(quantity + amount < 0)
        return State::NegativeQuantity;
    
    quantity += amount;
    return State::OK;
}

size_t Product::getProductID() const {
    return productId;
}

size_t Product::getOwnerID() const {
    return ownerId;
}

const char* Product::getName() const {
    return name;
}

void Product::print() const {
    std::cout << "Product: " << name << " x " << quantity << std::endl << 
                 "ID: " << productId << std::endl <<
                 "Owner: " << ownerId << std::endl << std::endl;
}