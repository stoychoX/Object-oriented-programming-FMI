#include "Restaurant.h"

void Restaurant::copyFrom(const Restaurant& other)
{
	strcpy(name, other.name);
	countProducts = other.countProducts;
	capacity = other.capacity;
	products = new Product * [capacity];
	minutesProductsCreation = new unsigned[capacity];
	for (size_t i = 0; i < countProducts; i++)
	{
		products[i] = new Product(*other.products[i]);
		minutesProductsCreation[i] = other.minutesProductsCreation[i];
	}
}
void Restaurant::moveFrom(Restaurant&& other)
{
	strcpy(name, other.name);
	countProducts = other.countProducts;
	capacity = other.capacity;
	products = other.products;
	minutesProductsCreation = other.minutesProductsCreation;
	other.name[0] = '\0';
	other.capacity = other.countProducts = 0;
	other.products = nullptr;
	other.minutesProductsCreation = nullptr;
}
void Restaurant::free()
{
	for (size_t i = 0; i < countProducts; i++)
	{
		delete products[i];
	}
	delete[] products;
	products = nullptr;
	delete[] minutesProductsCreation;
	minutesProductsCreation = nullptr;
	name[0] = '\0';
	capacity = countProducts = 0;
}
Restaurant::Restaurant(const Restaurant& other)
{
	copyFrom(other);
}
Restaurant::Restaurant(Restaurant&& other)
{
	moveFrom(std::move(other));
}
Restaurant& Restaurant::operator=(const Restaurant& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
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
Restaurant::Restaurant(const char name[25], size_t countProducts, size_t capacity,
	const Product** products, const unsigned* minutesProductsCreation)
{
	if (products == nullptr || minutesProductsCreation == nullptr)
	{
		throw std::invalid_argument("Argument string was nullptr!\n");
	}
	strcpy(this->name, name);
	this->countProducts = countProducts;
	this->capacity = capacity;
	this->products = new Product * [capacity];
	this->minutesProductsCreation = new unsigned[capacity];
	for (size_t i = 0; i < countProducts; i++)
	{
		this->products[i] = new Product(*products[i]);
		this->minutesProductsCreation[i] = minutesProductsCreation[i];
	}
}
static void resize(Product**& products, unsigned*& minutes, size_t count, size_t newCapacity)
{
	Product** newProducts = new Product * [newCapacity];
	unsigned* newMinutes = new unsigned[newCapacity];

	for (size_t i = 0; i < count; i++)
	{
		newProducts[i] = std::move(products[i]);
		newMinutes[i] = minutes[i];
	}
	delete[] products;
	delete[] minutes;
	products = newProducts;
	minutes = newMinutes;
}
void Restaurant::add(Product& product, unsigned minutesToCreate)
{
	if (contains(product) == -1)
	{
		if (countProducts == capacity)
		{
			resize(products, minutesProductsCreation,countProducts, capacity *= 2);
		}
		products[countProducts] = new Product(product);
		minutesProductsCreation[countProducts++] = minutesToCreate;
		std::cout << "Product added successfully!\n";
	}
	else
	{
		std::cout << "The product " << product.getName() << " already exists!\n";
	}
}
unsigned Restaurant::getOrder(Product** products, size_t count) const
{
	if (products == nullptr)
	{
		throw std::invalid_argument("Paramether was nullptr!\n");
	}
	unsigned countMinutesCreationOrder = 0;
	for (size_t i = 0; i < count; i++)
	{
		int indexProduct = contains(*products[i]);
		if (indexProduct == -1)
		{
			throw std::exception("No that product in the restaurant's menu!\n");
		}
		countMinutesCreationOrder += minutesProductsCreation[indexProduct];
	}
	return countMinutesCreationOrder;
}
int Restaurant::contains(const Product& product)const
{
	for (size_t i = 0; i < countProducts; i++)
	{
		if (strcmp(products[i]->getName().c_str(), product.getName().c_str()) == 0)
		{
			return i;
		}
	}
	return -1;
}
const char* Restaurant::getName()const
{
	return name;
}
void Restaurant::setName(const char newName[25])
{
	strcpy(name, newName);
	std::cout << "Name changed successfully!\n";
}