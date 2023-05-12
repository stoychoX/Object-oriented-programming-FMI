#include "Foodpanda.h"
void Foodpanda::copyFrom(const Foodpanda& other)
{
	count = other.count;
	capacity = other.capacity;
	restaurants = new Restaurant * [count];
	for (size_t i = 0; i < count; i++)
	{
		restaurants[i] = new Restaurant(*other.restaurants[i]);//that should not throw
	}
}
void Foodpanda::moveFrom(Foodpanda&& other)
{
	count = other.count;
	capacity = other.capacity;
	restaurants = other.restaurants;
	other.restaurants = nullptr;
	other.count = other.capacity = 0;
}
void Foodpanda::free()
{
	for (size_t i = 0; i < count; i++)
	{
		Restaurant* a = restaurants[i];
		delete restaurants[i];
	}
	delete[] restaurants;
	restaurants = nullptr;
	count = capacity = 0;
}
Foodpanda::Foodpanda(const Foodpanda& other)
{
	copyFrom(other);
}
Foodpanda::Foodpanda(Foodpanda&& other)
{
	moveFrom(std::move(other));
}
Foodpanda& Foodpanda::operator=(const Foodpanda& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Foodpanda& Foodpanda::operator=(Foodpanda&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Foodpanda::~Foodpanda()
{
	free();
}
Foodpanda::Foodpanda(const Restaurant** restaurants, size_t count, size_t capacity)
{
	if (restaurants == nullptr)
	{
		throw std::invalid_argument("Paramether was nullptr!\n");
	}
	this->count = count;
	this->capacity = capacity;
	this->restaurants = new Restaurant * [capacity];
	for (size_t i = 0; i < count; i++)
	{
		try
		{
			this->restaurants[i] = new Restaurant(*restaurants[i]);
		}
		catch (const std::invalid_argument& ex)
		{
			for (size_t j = 0; j < i; j++)//should I delete that here???
			{
				delete this->restaurants[i];
			}
			delete[] this->restaurants;
			std::cout << ex.what() << " Thrown at index: " << i << std::endl;
		}
		catch (const std::exception& ex)
		{
			for (size_t j = 0; j < i; j++)
			{
				delete this->restaurants[i];
			}
			delete[] this->restaurants;
			std::cout << ex.what() << " Thrown at index: " << i << std::endl;
		}
	}
}
static int getIndexRestaurant(Restaurant** restaurants, const Restaurant& rest, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(restaurants[i]->getName(), rest.getName()) == 0)
		{
			return i;
		}
	}
	return -1;
}
bool Foodpanda::getOrder(const Order& order)
{
	if (order.getDest() == nullptr)
	{
		std::cout << "No such restaurant found!\n";
		return false;
	}
	int indexRest = getIndexRestaurant(restaurants, *order.getDest(), count);
	if (indexRest == -1)
	{
		std::cout << "No such restaurant found!\n";
		return false;
	}
	unsigned countMinutesToWait = 0;
	try
	{
		countMinutesToWait = restaurants[indexRest]
			->getOrder(order.getProducts(), order.getCountProducts());
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what();
		return false;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return false;
	}
	std::cout << "Order accepted! Wait " << countMinutesToWait << " more minutes!\n";
	return true;
}
void Foodpanda::addProductIn(const Restaurant& rest, Product& product, unsigned minutesToCreate)
{
	int indexRest = getIndexRestaurant(restaurants, rest, count);
	if (indexRest == -1)
	{
		std::cout << "No such restaurant found!\n";
		return;
	}
	restaurants[indexRest]->add(product, minutesToCreate);
}
static void resize(Restaurant** rest, size_t count, size_t newCapacity)
{
	Restaurant** newRest = new Restaurant * [newCapacity];
	for (size_t i = 0; i < count; i++)
	{
		newRest[i] = std::move(rest[i]);
	}
	delete[] rest;
	rest = newRest;
}
void Foodpanda::addRestaurant(Restaurant& rest)
{
	int indexRest = getIndexRestaurant(restaurants, rest, count);
	if (indexRest == -1)
	{
		if (count == capacity)
		{
			resize(restaurants, count, capacity *= 2);
		}
		restaurants[count++] = new Restaurant(rest);//that should not throw
		std::cout << "Restaurant added successfully!\n";
	}
	else
	{
		std::cout << rest.getName() << " already exists in the system!\n"
			<< "Try to change the name if the restaurant is new!\n";
	}
}