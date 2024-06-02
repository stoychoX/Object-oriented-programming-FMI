#pragma once
#include "polymorphic_ptr.hpp"
#include <vector>

template<class T>
class polymorphic_container
{
private:
	std::vector<polymorphic_ptr<T>> data;
public:
	void add(T*);

	polymorphic_ptr<T>& operator[](size_t idx);
	const polymorphic_ptr<T>& operator[](size_t idx) const;

	void execute(size_t idx, void (*func)(T*));
	void execute(size_t idx, void (*func)(const T*)) const;
};

template<class T>
void polymorphic_container<T>::add(T* ptr)
{
	data.push_back(ptr);
}

template<class T>
polymorphic_ptr<T>& polymorphic_container<T>::operator[](size_t idx)
{
	return data[idx];
}

template<class T>
const polymorphic_ptr<T>& polymorphic_container<T>::operator[](size_t idx) const
{
	return data[idx];
}

template<class T>
void polymorphic_container<T>::execute(size_t idx, void(*func)(T*))
{
	func(data[idx].get());
}
