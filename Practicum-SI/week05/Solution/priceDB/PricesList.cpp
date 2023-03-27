#include"PricesList.h"

PricesList::PricesList() : size {0} {}

State PricesList::addPrice(size_t itemID, double price) {
    if(size == 50)
        return State::PriceFull;
    

    // Ако продуктът съществува ъпдейтваме цената му
    for (size_t i = 0; i < size; i++) {
        if (prices[i].getId() == itemID) {
            // С колко се увеличава или намалява
            double priceDiff = price - prices[i].getPrice();

            prices[i].updatePrice(priceDiff);

            return State::OK;
        }
    }

    prices[size++] = Price(itemID, price);
    return State::OK;
}

double PricesList::getPrice(size_t id) const {
    for (size_t i = 0; i < size; i++)
        if(prices[i].getId() == id)
            return prices[i].getPrice();

    return 0;        
}

void PricesList::print() const {
    for (size_t i = 0; i < size; i++)
        prices[i].print();
}
