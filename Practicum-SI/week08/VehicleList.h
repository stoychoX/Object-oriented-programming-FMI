#pragma once
#include "Vehicle.h"
class VehicleList
{
	Vehicle** vehicles = nullptr;
	size_t _capacity = 0;
	size_t _size = 0;
	void copyFrom(const VehicleList& other);
	void free();
public:
	VehicleList(const VehicleList& other);
	VehicleList& operator=(const VehicleList& other);
	~VehicleList();
	VehicleList(size_t capacity);
	void insert(const char* reg, const char* desc);
	const Vehicle& at(size_t index) const;
	const Vehicle& operator[](size_t pos) const;
	bool empty() const;
	size_t capacity() const;
	size_t size() const;
	const Vehicle* find(const Registration& regnum) const;
}; 