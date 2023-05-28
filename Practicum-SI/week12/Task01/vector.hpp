#pragma once

template <typename T>
class vector
{
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 8;
	void free();
	void copyFrom(const vector<T>& other);
	void moveFrom(vector<T>&& other);
	void resize(size_t capacity);

public:
	vector();
	vector(size_t size);
	vector(size_t size, const T& element);
	vector(const vector<T>& other);
	vector(vector<T>&& other);

	vector<T>& operator=(const vector<T>& other);
	vector<T>& operator=(vector<T>&& other);
	~vector<T>();

	void push_back(const T& element);
	void push_back(const T&& element);
	void pop_back();
	const T& operator[](size_t at) const;
	T& operator[](size_t at);
	bool empty() const;
	size_t size() const;
	size_t capacity() const;
	void clear();
};

template <typename T>
void vector<T>::free()
{
	delete[] _data;
	_size = _capacity = 0;
}

template <typename T>
void vector<T>::copyFrom(const vector<T>& other)
{
	_data = new T[other._capacity];
	_size = other._size;
	_capacity = other._capacity;
	for (size_t i = 0; i < other._size; i++)
	{
		_data[i] = other._data[i];
	}
}
template <typename T>
void vector<T>::moveFrom(vector<T>&& other)
{
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	other._data = nullptr;
	other._size = other._capacity = 0;
}

template <typename T>
void vector<T>::resize(size_t capacity)
{
	T* newData = new T[capacity];
	_capacity = capacity;
	for (size_t i = 0; i < _size; i++)
	{
		newData[i] = std::move(_data[i]);
	}
	delete[] _data;
	_data = newData;
}

template <typename T>
vector<T>::vector()
{
	_data = new T[_capacity];
}
template <typename T>
vector<T>::vector(size_t size) :_size(size), _capacity(size)
{
	_data = new T[_capacity];
}

template <typename T>
vector<T>::vector(size_t size, const T& element) : _size(size), _capacity(size)
{
	_data = new T[_capacity]{ element };//?
}
template <typename T>
vector<T>::vector(const vector<T>& other)
{
	copyFrom(other);
}
template <typename T>
vector<T>::vector(vector<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
}
template <typename T>
vector<T>::~vector<T>()
{
	free();
}

template <typename T>
void vector<T>::push_back(const T& element)
{
	if (_size == _capacity)
	{
		resize(_capacity * 2);
	}
	_data[_size++] = element;
}

template <typename T>
void vector<T>::push_back(const T&& element)
{
	if (_size == _capacity)
	{
		resize(_capacity * 2);
	}
	_data[_size++] = std::move(element);
}

template <typename T>
void vector<T>::pop_back()
{
	if (_size > 0)
	{
		_size--;
	}
	if (_size == _capacity / 4)
	{
		resize(_capacity / 4);
	}
}
template <typename T>
const T& vector<T>::operator[](size_t at) const
{
	return _data[at];
}
template <typename T>
T& vector<T>::operator[](size_t at)
{
	return _data[at];
}
template <typename T>
bool vector<T>::empty() const
{
	return _size == 0;
}
template <typename T>
size_t vector<T>::size() const
{
	return _size;
}
template <typename T>
size_t vector<T>::capacity() const
{
	return _capacity;
}
template <typename T>
void vector<T>::clear()
{
	/*for (size_t i = 0; i < _size; i++)
	{
		_data[i].~T();
	}*/
	_size = 0;
}