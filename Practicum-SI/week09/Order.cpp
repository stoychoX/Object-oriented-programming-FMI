#include "Order.h"

void Order::copyFrom(const Order& other)
{
	to = other.to;//is that correct or to create new restaurant
	countProducts = other.countProducts;
	products = new Product * [countProducts];
	for (size_t i = 0; i < countProducts; i++)
	{
		products[i] = new Product(*other.products[i]);
	}
}
void Order::moveFrom(Order&& other)
{
	to = other.to;
	countProducts = other.countProducts;
	products = other.products;
	other.products = nullptr;
	other.to = nullptr;
	other.countProducts = 0;
}
void Order::free()
{
	for (size_t i = 0; i < countProducts; i++)
	{
		delete products[i];
	}
	delete[] products;
	products = nullptr;
	to = nullptr;
	countProducts = 0;
}
Order::Order(Restaurant* to, size_t countProducts,const Product** products)
{
	if (to == nullptr || products == nullptr)
	{
		throw std::invalid_argument("Nullptr was taken as argument!");
	}
	this->to = to;
	this->countProducts = countProducts;
	this->products = new Product * [countProducts];
	for (size_t i = 0; i < countProducts; i++)
	{
		this->products[i] = new Product(*products[i]);
	}
}
Order::Order(const Order& other)
{
	copyFrom(other);
}
Order::Order(Order&& other)
{
	moveFrom(std::move(other));
}
Order& Order::operator=(const Order& other)
{
	if (this!=&other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Order& Order::operator=(Order&& other)
{
	if (this!=&other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Order::~Order()
{
	free();
}
const Restaurant* Order::getDest() const
{
	return to;
}
size_t Order::getCountProducts()const
{
	return countProducts;
}
Product** Order::getProducts()const
{
	return products;
}