#include"Price.h"

Price::Price() : productId{0}, price{0} {}

Price::Price(size_t id, double p) : productId{id}, price{ std::abs(p) } {}

size_t Price::getId() const {
    return productId;
}

double Price::getPrice() const {
    return price;
}

State Price::updatePrice(double amount) {
    if(price + amount < 0)
        return State::NegativePrice;
    
    price += amount;
    return State::OK;
}

void Price::print() const {
    std::cout << "ID: " << productId << std::endl << "Price " << price << std::endl;
}
