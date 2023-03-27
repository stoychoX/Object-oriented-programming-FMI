#include"SalesSystem.h"

SalesSystem::SalesSystem() {}

State SalesSystem::addUser(const char* name, double balance) {
    return users.addUser(name, balance);
}

State SalesSystem::addProduct(const char* name, size_t ownerID, size_t quantity) {
    if(!users.existUser(ownerID))
        return State::UserNotFound;
    
    return products.addProduct(name, ownerID, quantity);
}

State SalesSystem::addPrice(size_t productID, double price) {
    if(!products.existProduct(productID))
        return State::ProductNotFound;
    
    return prices.addPrice(productID, price);
}

State SalesSystem::sell(size_t idFrom, size_t idTo, size_t productID, size_t quantity) {
    if(products.isFull())
        return State::ProductFull;

    if(!users.existUser(idFrom) || !users.existUser(idTo))
        return State::UserNotFound;
    
    if(!products.existProduct(productID))
        return State::ProductNotFound;
    
    double price = prices.getPrice(productID) * quantity;

    if(!users.hasEnough(idTo, price))
        return State::ShortOnMoney;
    
    if(products.itemsOwned(idFrom, productID) < quantity) 
        return State::NotEnoughItems;
    
    if(products.itemsOwned(idTo, productID) == 0) {
        const char* name = products.getName(productID);

        if(name == nullptr)
            return State::ProductNotFound;

        products.addProduct(name, idTo, 0);
    }

    // Продаващия губи а купуващия печели бройки
    products.update(idFrom, productID, -1 * ((int)(quantity)) );
    products.update(idTo, productID, quantity);

    // Продаващия печели пари а купуващия губи
    users.update(idFrom, price);
    users.update(idTo, -price);

    // Грижим се ако потребителя е продал всички продукти продуктът да се
    // премахне от базата
    products.cleanupDatabase();

    return State::OK;
}

void SalesSystem::print(const char* msg) const {
    for (size_t i = 0; i < 25; i++)
        std::cout << '=';
    
    std::cout << msg;
    
    for (size_t i = 0; i < 25; i++)
        std::cout << '=';
    std::cout << std::endl;

    std::cout << "Users: " << std::endl;
    users.printAllUsers();


    std::cout << std::endl;
    std::cout << "Products: " << std::endl;
    products.print();

    std::cout << std::endl;
    std::cout << "Prices: " << std::endl;
    prices.print();
}