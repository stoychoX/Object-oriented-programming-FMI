#include "VehicleList.h"

void VehicleList::copyFrom(const VehicleList& other)
{
	vehicles = new Vehicle * [other._capacity];
	for (size_t i = 0; i < other._size; i++)
	{
		//here other is correct, so we do not expect to throw
		vehicles[i] = new Vehicle(*other.vehicles[i]);
	}
	_size = other._size;
	_capacity = other._capacity;
}
void VehicleList::free()
{
	for (size_t i = 0; i < _size; i++)
	{
		delete vehicles[i];
	}
	delete[] vehicles;
}
VehicleList::VehicleList(const VehicleList& other)
{
	copyFrom(other);
}
VehicleList& VehicleList::operator=(const VehicleList& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
VehicleList::~VehicleList()
{
	free();
}
VehicleList::VehicleList(size_t capacity)
{
	vehicles = new Vehicle * [capacity];
	_capacity = capacity;
}
static size_t getIndexToInsert(Vehicle** vehicles, size_t size, const char* reg)
{
	int start = 0;
	int end = size - 1;
	size_t indexMid = 0;
	while (start <= end)
	{
		indexMid = (start + end) / 2;
		int result = strcmp(reg, vehicles[indexMid]->getReg()->toString());
		if (result == 0)
		{
			break;
		}
		if (result < 0)
		{
			end = indexMid - 1;
		}
		else
		{
			start = indexMid + 1;
		}
	}
	if (start > indexMid)
	{
		return start;
	}
	return indexMid;
}
static int getIndexElementByBinarySearch(Vehicle** vehicles, size_t size, const char* reg)
{
	int start = 0;
	int end = size - 1;
	size_t indexMid = 0;
	while (start <= end)
	{
		indexMid = start + (end - start) / 2;
		int result = strcmp(reg, vehicles[indexMid]->getReg()->toString());
		if (result == 0)
		{
			return indexMid;
		}
		if (result < 0)
		{
			end = indexMid - 1;
		}
		else
		{
			start = indexMid + 1;
		}
	}
	return -1;
}
void VehicleList::insert(const char* reg, const char* desc)
{
	//keeping vehicles sorted
	if (reg == nullptr || desc == nullptr)
	{
		throw std::invalid_argument("String does not exist!");
	}
	if (_size == _capacity)
	{
		throw std::exception("The list is full!");
	}
	if (find(reg) != nullptr)
	{
		throw std::exception("Vehicle already exists!");
	}
	size_t indexToInsert = getIndexToInsert(vehicles, _size, reg);
	for (size_t i = _size; i > indexToInsert; i--)
	{
		vehicles[i] = vehicles[i - 1];
	}
	vehicles[indexToInsert] = new Vehicle(reg, desc);;
	_size++;
}
const Vehicle& VehicleList::at(size_t index) const
{
	if (index >= _size)
	{
		throw std::exception("Invalid index!");
	}
	return *vehicles[index];
}
const Vehicle& VehicleList::operator[](size_t pos) const
{
	return *vehicles[pos];
}
bool VehicleList::empty() const
{
	return _size == 0;
}
size_t VehicleList::capacity() const
{
	return _capacity;
}
size_t VehicleList::size() const
{
	return _size;
}
const Vehicle* VehicleList::find(const Registration& regnum) const
{
	//using binary search to make thetha logn
	int indexVehicle = getIndexElementByBinarySearch(vehicles, _size, regnum.toString());
	if (indexVehicle == -1)
	{
		return nullptr;
	}
	return vehicles[indexVehicle];
}