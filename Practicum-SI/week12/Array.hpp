#pragma once
#include <stdexcept>

template <typename T, size_t S>
class Array {
private:
	T data[S]{};
public:
	size_t size() const;
	bool empty() const;
	void fill(const T& element);
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
};

template <typename T, size_t S>
size_t Array<T, S>::size() const {
	return S;
}
template <typename T, size_t S>
bool Array<T, S>::empty() const {
	return S == 0;
}
template <typename T, size_t S>
void Array<T, S>::fill(const T& element) {
	for (size_t i = 0; i < S; i++) {
		data[i] = element;
	}
}
template <typename T, size_t S>
const T& Array<T, S>::operator[](size_t index) const {
	if (index >= S) {
		throw std::out_of_range("Index outside the range of the array!");
	}

	return data[index];
}
template <typename T, size_t S>
T& Array<T, S>::operator[](size_t index) {
	if (index >= S) {
		throw std::out_of_range("Index outside the range of the array!");
	}

	return data[index];
}