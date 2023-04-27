#pragma once
#include "Product.h"

const int MAX_NAME_SIZE = 25;

class Restaurant
{
	char name[MAX_NAME_SIZE + 1]{ '\0' };
	size_t productCount;
	Product** listOfProducts;
	size_t listOfPrCapacity;
	size_t listOfPrSize;
	void free();
	void moveFrom(Restaurant&& other);
public:
	Restaurant() = default;
	Restaurant(const Restaurant& other) = delete;
	Restaurant(Restaurant&& other);
	Restaurant& operator=(const Restaurant& other) = delete;
	Restaurant& operator=(Restaurant&& other);
	~Restaurant();

	void addProduct(const char* name);


};