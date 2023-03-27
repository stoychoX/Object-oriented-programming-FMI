#include"ProductDatabase.h"

namespace IDBuffer {
    size_t productIndex = 0;
}

ProductDatabase::ProductDatabase() : size { 0 } {}

State ProductDatabase::addProduct(const char* name, size_t ownerID, size_t quantity) {
    if(size == 50)
        return State::ProductFull;
    
    size_t productID = 0;

    // Ако продуктът съществува не създаваме ново id
    for (size_t i = 0; i < size; i++) {
        if (strcmp(products[i].getName(), name) == 0) {
            productID = products[i].getProductID();
            
            // Ако потребителя вече има от този продукт просто увеличаваме 
            // броя на продуктите които има.
            if (products[i].getOwnerID() == ownerID)
                return products[i].changeQuantity(1);
        }
    }

    if(productID == 0)
        productID = ++IDBuffer::productIndex;    


    products[size++] = Product(name, productID, ownerID, quantity);
    return State::OK;
}

const char* ProductDatabase::getName(size_t productID) const {
    for (size_t i = 0; i < size; i++)
        if(products[i].getProductID() == productID)
            return products[i].getName();
    return nullptr;
}

bool ProductDatabase::existProduct(size_t id) const {
    for (size_t i = 0; i < size; i++)
        if(products[i].getProductID() == id) 
            return true;
    return false;
}

size_t ProductDatabase::itemsOwned(size_t id, size_t productID) const {
    for (size_t i = 0; i < size; i++)
        if(products[i].getProductID() == productID && products[i].getOwnerID() == id)
            return products[i].getQuantity();
    
    return 0;
}

State ProductDatabase::update(size_t id, size_t productID, int update) {
    for (size_t i = 0; i < size; i++) {
        if(products[i].getOwnerID() == id && products[i].getProductID() == productID) {
            return products[i].changeQuantity(update);
        }
    }
    return State::ProductNotFound;
}  

bool ProductDatabase::isFull() const {
    return size == 50;
}

void ProductDatabase::print() const {
    for (size_t i = 0; i < size; i++)
        products[i].print();    
}

void ProductDatabase::cleanupDatabase() {
    for (size_t i = 0; i < size; i++) {
        if(products[i].getQuantity() == 0) {
            std::swap(products[i], products[size - 1]);
            size--;
        }
    }
}