#pragma once

template <typename T>
class Vector
{
	T* data;
	size_t capacity;
	size_t size;
	void copyFrom(const Vector& other)
	{
		data = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;
		for (size_t i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}
	}
	void free()
	{
		delete[] data;
		data = nullptr;
		size = capacity = 0;
	}
	void moveFrom(Vector&& other)
	{
		data = other.data;
		other.data = nullptr;
		size = other.size;
		capacity = other.capacity;
	}
	void resize(size_t cap)
	{
		T* newData = new T[cap];
		for (size_t i = 0; i < capacity; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		capacity = cap;
	}
public:
	Vector()
	{
		data = nullptr;
		capacity = 8;
		size = 0;
	}
	Vector(size_t n)
	{
		capacity = n;
		size = n;
		data = new T[n];
	}
	Vector(size_t n, const T& elem) : Vector(n)
	{
		for (size_t i = 0; i < n; i++)
		{
			data[i] = elem;
		}
	}
	Vector(const T& other)
	{
		copyFrom(other);
	}
	Vector(T&& other)
	{
		moveFrom(std::move(other));
	}
	Vector& operator=(const T& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}
	Vector& operator=(T&& other)
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}
		return *this;
	}
	void push_back(const T& elem)
	{
		resize(2 * capacity);
		data[size++] = elem;
	}
	void pop_back()
	{
		size--;
	}
	const T& operator[](size_t ind) const
	{
		return data[ind];
	}
	T& operator[](size_t ind)
	{
		return data[ind];
	}
	bool isEmpty() const
	{
		return size == 0;
	}
	size_t getSize() const
	{
		return size;
	}
	size_t getCapacity() const
	{
		return capacity;
	}
	void clear()
	{
		size = 0;
	}
	~Vector()
	{
		free();
	}
};
