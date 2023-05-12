#pragma once
#include "Product.h"
class Restaurant
{
	char name[25];
	size_t countProducts = 0;
	size_t capacity = 0;
	Product** products = nullptr;
	unsigned* minutesProductsCreation = nullptr;
	void copyFrom(const Restaurant& other);
	void moveFrom(Restaurant&& other);
	void free();
public:
	Restaurant(const Restaurant& other);
	Restaurant(Restaurant&& other);
	Restaurant& operator=(const Restaurant& other);
	Restaurant& operator=(Restaurant&& other);
	~Restaurant();
	Restaurant(const char name[25], size_t countProducts, size_t capacity,
		const Product** products, const unsigned* minutesProductsCreation);
	void add(Product& product, unsigned minutesToCreate);
	unsigned getOrder(Product** products, size_t count) const;
	int contains(const Product& product)const;
	const char* getName()const;
	void setName(const char newName[25]);

};