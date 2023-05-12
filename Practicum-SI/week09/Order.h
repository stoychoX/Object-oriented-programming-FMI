#pragma once
#include "Restaurant.h"
class Order
{
	Restaurant* to = nullptr;
	size_t countProducts = 0;
	Product** products = nullptr;
	void copyFrom(const Order& other);
	void moveFrom(Order&& other);
	void free();
public:
	Order(Restaurant* to, size_t countProducts,const Product** products);
	Order(const Order& other);
	Order(Order&& other);
	Order& operator=(const Order& other);
	Order& operator=(Order&& other);
	~Order();
	const Restaurant* getDest() const;
	size_t getCountProducts()const;
	Product** getProducts()const;
};