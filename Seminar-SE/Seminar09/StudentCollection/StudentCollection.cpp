#include "StudentCollection.h"
#include <stdexcept>

void StudentCollection::free()
{
	for (size_t i = 0; i < capacity; i++)
		delete data[i];

	delete[] data;
}

void StudentCollection::copyFrom(const StudentCollection& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new Student*[capacity] {};

	for (size_t i = 0; i < capacity; i++)
	{
		if (other.data[i] != nullptr)
		{
			*data[i] = *other.data[i];
		}
	}
}

void StudentCollection::move(StudentCollection&& other)
{
	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;
}

void StudentCollection::resize(size_t newCap)
{
	if (newCap <= capacity)
		return;
	Student** newData = new Student * [newCap] {};

	for (size_t i = 0; i < capacity; i++)
		newData[i] = data[i];
	
	delete[] data;
	data = newData;
	capacity = newCap;
}

size_t StudentCollection::getLastFreeIndex() const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (data[i] == nullptr)
			return i;
	}
	return capacity;
}

StudentCollection::StudentCollection() : size(0), capacity(8)
{
	data = new Student * [capacity] {};
}

StudentCollection::StudentCollection(const StudentCollection& other)
{
	copyFrom(other);
}

StudentCollection& StudentCollection::operator=(const StudentCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void StudentCollection::pushAt(size_t idx, const Student& other)
{
	if (idx > capacity)
		throw std::out_of_range("StudentCollection::pushAt invalid");

	if (data[idx] == nullptr)
	{
		data[idx] = new Student(other);
		++size;
	}
	else
	{
		*data[idx] = other;
	}
}

void StudentCollection::pushAt(size_t idx, Student&& other)
{
	if (idx > capacity)
		throw std::out_of_range("StudentCollection::pushAt invalid");

	if (data[idx] == nullptr)
	{
		data[idx] = new Student(std::move(other));
		++size;
	}
	else
	{
		*data[idx] = std::move(other);
	}
}

void StudentCollection::push(const Student& student)
{
	size_t index = getLastFreeIndex();
	if (index == capacity)
		resize(capacity + capacity / 2);
	pushAt(index, student);
}

void StudentCollection::push(Student&& student)
{
	size_t index = getLastFreeIndex();
	if (index == capacity)
		resize(capacity + capacity / 2);
	pushAt(index, std::move(student));
}

void StudentCollection::removeAt(size_t idx)
{
	if (idx >= capacity)
		throw std::out_of_range("StudentCollection::removeAt invalid index");

	if (!contains(idx))
		return;

	delete data[idx];
	data[idx] = nullptr;
	size--;
}

bool StudentCollection::contains(size_t idx) const
{
	return (data[idx] != nullptr);
}

const Student& StudentCollection::at(size_t idx) const
{
    if(idx >= capacity)
        throw std::out_of_range("StudentCollection::at invalid index!");
    
    if(!contains(idx))
        throw std::runtime_error("StudentCollection::at trying to access empty object");
    
    return *data[idx];
}

size_t StudentCollection::getCapacity() const
{
    return capacity;
}


StudentCollection& StudentCollection::operator=(StudentCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

StudentCollection::StudentCollection(StudentCollection&& other) noexcept
{
	move(std::move(other));
}

size_t StudentCollection::getSize() const
{
    return size;
}

StudentCollection::~StudentCollection()
{
	free();
}