#include <iostream>
#include "Foodpanda.h"

int main()
{
	Product a("tomato");
	Product b("apple");
	Product c("ice cream");
	const Product** products = new  const Product * [3] {&a, & b, & c};
	const unsigned* minutes = new unsigned[3] {10, 20, 15};
	Restaurant rest("R1", 3, 3, products, minutes);

	Product a2("orange");
	Product b2("mapple surup");
	Product c2("ice");
	Product d2("pagakia");
	const Product** products2 = new const Product * [4] {&a2, & b2, & c2, & d2};
	const unsigned* minutes2 = new unsigned[4] {10, 2, 5, 10};
	Restaurant rest2("R2", 4, 12, products2, minutes2);

	Product a3("chilli");
	Product b3("soup");
	Product c3("apricot");
	Product d3("spagetti");
	const Product** products3 = new const Product * [4] {&a3, & b3, & c3, & d3};
	const unsigned* minutes3 = new unsigned[4] {10, 2, 5, 10};
	Restaurant rest3("R3", 4, 12, products3, minutes3);

	const Restaurant** restTwo = new const Restaurant * [2] {&rest, & rest2};
	Foodpanda food1(restTwo, 2, 10);

	const Product** productsOrder = new const Product * [1] {&b3};

	Order order(&rest3, 1, productsOrder);
	food1.getOrder(order);

	food1.addRestaurant(rest3);
	//food1.addProductIn(rest3, a, 100);
	food1.getOrder(order);
	//const Product** productsOrder = new const Product * [1] {&c3};

	//Order order(&newRest, 1, productsOrder);
	//food1.addRestaurant(rest);
	//newRest.setName("Hello");
	//food1.addRestaurant(newRest);
	//food1.getOrder(order);
	//Restaurant newRest = std::move(rest);
}
