#pragma once
#include "Restaurant.h"
#include "Order.h"
class Foodpanda
{
	Restaurant** restaurants = nullptr;
	size_t count = 0;
	size_t capacity = 0;
	void copyFrom(const Foodpanda& other);
	void moveFrom(Foodpanda&& other);
	void free();
public:
	Foodpanda(const Foodpanda& other);
	Foodpanda(Foodpanda&& other);
	Foodpanda& operator=(const Foodpanda& other);
	Foodpanda& operator=(Foodpanda&& other);
	~Foodpanda();
	Foodpanda(const Restaurant** restaurants, size_t count, size_t capacity);
	bool getOrder(const Order& order);
	void addProductIn(const Restaurant& rest, Product& product, unsigned minuteToCreate = 0);
	void addRestaurant(Restaurant& rest);
};//where to put const and how in 2d dynamic arrays?