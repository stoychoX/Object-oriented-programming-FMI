#pragma once

template <typename T, size_t len>
class array
{
	T _data[len];
	size_t _len = len;
	size_t _count = 0;
public:
	size_t size() const;
	bool empty() const;
	void fill(T element);
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
};

template <typename T, size_t len>
size_t array<T, len>::size() const
{
	return _len;
}

template<typename T, size_t len>
bool array<T, len>::empty() const
{
	return _count == 0;
}

template <typename T, size_t len>
void array<T, len>::fill(T element)
{
	for (size_t i = 0; i < _len; i++)
	{
		_data[i] = element;
	}
	_count = _len;
}

template <typename T, size_t len>
const T& array<T, len>::operator[](size_t index) const
{
	return _data[index];
}

template <typename T, size_t len>
T& array<T, len>::operator[](size_t index)
{
	return _data[index];
}