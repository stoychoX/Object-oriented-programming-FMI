#include<iostream>
#include"SalesSystem.h"

// За улеснение дефинираме ID тата на потребителите
#define NIKOLA 1
#define YAVOR 2
#define HRISTO 3

// и на продуктите
#define LAPTOP 1
#define CAR 2
#define OOP_ANSWERS 3

int main() {
    SalesSystem sys;

    sys.addUser("Nikola", 10'000.0);     // id: 1
    sys.addUser("Yavor", 20'000);        // id: 2
    sys.addUser("Hristo", 15'000);       // id: 3

    sys.addProduct("Laptop", NIKOLA, 2); // Никола има 2 лаптопа
    sys.addPrice(1, 1000.0);             // Които струват 1000

    sys.addProduct("Car", HRISTO, 1);     
    sys.addPrice(2, 10'000);

    sys.addProduct("OOP exam answers", NIKOLA, 1);
    sys.addPrice(OOP_ANSWERS, 1'000'000.0);

    sys.print("Before sales");
    
    sys.sell(NIKOLA, YAVOR, LAPTOP, 1);
    sys.print("After selling laptop from 1 to 2");

    sys.sell(NIKOLA, HRISTO, LAPTOP, 1);
    sys.print("After selling laptop from 1 to 3");

    sys.addPrice(LAPTOP, 1200);
    sys.print("After updating laptop price");

    sys.addPrice(LAPTOP, -3);
    sys.print("Trying to set negative price on laptop");

    sys.sell(NIKOLA, YAVOR, OOP_ANSWERS, 1);
    sys.print("After trying to sell OOP_ANSWERS from 1 to 2");
}