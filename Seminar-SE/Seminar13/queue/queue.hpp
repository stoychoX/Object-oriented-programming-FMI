#pragma once
#include <stdexcept>
template<class T>
class Queue
{
private:
	size_t head;
	size_t tail;

	size_t size;
	size_t capacity;

	T* data;

	void free();
	void copyFrom(const Queue& other);

	void resize(size_t newCapacity);
public:
	Queue();

	Queue(const Queue&);
	Queue& operator=(const Queue&);

	void push(const T&);
	void pop();
	const T& top() const;

	bool empty() const;

	~Queue();
};

template<class T>
inline void Queue<T>::free()
{
	delete[] data;
	data = nullptr;
	head = tail = size = capacity = 0;
}

template<class T>
inline void Queue<T>::copyFrom(const Queue<T>& other)
{
	size = 0;
	capacity = other.capacity;

	data = new T[other.capacity];

	size_t otherHead = other.head;
	size_t otherTail = other.tail;

	while (otherHead != otherTail)
	{
		push(other.data[otherTail]);
		(++otherTail) %= capacity;
	}
}

template<class T>
inline void Queue<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];

	size_t at = 0;

	while (!empty() && at < newCapacity)
	{
		newData[at++] = top();
		pop();
	}
	delete[] data;
	data = newData;
	capacity = newCapacity;
	
	head = at;
	tail = 0;
	size = at;
}

template<class T>
inline Queue<T>::Queue() :
	head(0),
	tail(0),
	size(0),
	capacity(8),
	data(nullptr)
{
	data = new T[capacity]{};
}

template<class T>
inline Queue<T>::Queue(const Queue& other)
{
	copyFrom(other);
}

template<class T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
inline void Queue<T>::push(const T& arg)
{
	if (size == capacity)
	{
		resize(2 * capacity);
	}
	data[head] = arg;
	(++head) %= capacity;
	++size;
}

template<class T>
inline void Queue<T>::pop()
{
	if (empty())
		throw std::runtime_error("Empty queue");
	
	(++tail) %= capacity;
	--size;
}

template<class T>
inline const T& Queue<T>::top() const
{
	if (empty())
		throw std::runtime_error("Emty queue on top()");

	return data[tail];
}

template<class T>
inline bool Queue<T>::empty() const
{
	return size == 0;
}

template<class T>
inline Queue<T>::~Queue()
{
	free();
}