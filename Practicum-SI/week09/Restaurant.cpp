#include "Restaurant.h"
#include <cstring>
#include <iostream>

void Restaurant::free()
{
	for (size_t i = 0; i < listOfPrCapacity; i++)
	{
		delete[] listOfProducts[i];
	}
	delete[] listOfProducts;
}
void Restaurant::moveFrom(Restaurant&& other)
{
	strcpy(this->name, other.name);
	this->productCount = other.productCount;
	this->listOfPrSize = other.listOfPrSize;
	this->listOfPrCapacity = other.listOfPrCapacity;
	for (size_t i = 0; i < listOfPrCapacity; i++)
	{
		this->listOfProducts[i] = other.listOfProducts[i];
		other.listOfProducts[i] = nullptr;
	}
	this->listOfProducts = other.listOfProducts;
	other.listOfProducts = nullptr;
}

Restaurant::Restaurant(Restaurant&& other)
{
	moveFrom(std::move(other));
}
Restaurant& Restaurant::operator=(Restaurant&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Restaurant::~Restaurant()
{
	free();
}
void Restaurant::addProduct(const char* name)
{
	//if(listOfPrSize == listOfPrCapacity)
		//resize
	listOfProducts[listOfPrSize++] = new Product(name);
}