#pragma once
#include <stdexcept>

template <typename T>
class Vector {
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void free();
	void resize();
public:
	Vector() = default;
	Vector(size_t capacity);
	Vector(size_t capacity, const T& element);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();

	void push_back(const T& element);
	void pop_back();
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	bool empty() const;
	size_t size() const;
	size_t capacity() const;
	void clear();
};

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	this->data = new T[other.capacity]{};
	for (size_t i = 0; i < other.size; i++) {
		this->data[i] = other.data[i];
	}
	this->size = other.size;
	this->capacity = other.capacity;
}
template <typename T>
void Vector<T>::moveFrom(Vector<T>&& other) {
	this->data = other.data;
	other.data = nullptr;
	this->size = other.size;
	this->capacity = other.capacity;
}
template <typename T>
void Vector<T>::free() {
	delete this->data;
}
template <typename T>
void Vector<T>::resize() {
	T* temp = new T[this->capacity * 2]{};
	for (size_t i = 0; i < this->capacity; i++) {
		temp[i] = this->data[i];
	}

	delete[] this->data;
	this->data = temp;
	this->capacity *= 2;
}

template <typename T>
Vector<T>::Vector(size_t capacity) {
	this->data = new T[capacity]{};
	this->size = capacity;
	this->capacity = capacity;
}
template <typename T>
Vector<T>::Vector(size_t capacity, const T& element) : Vector(capacity) {
	for (size_t i = 0; i < capacity; i++) {
		this->data[i] = element;
	}
}
template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
	this->copyFrom(other);
}
template <typename T>
Vector<T>::Vector(Vector<T>&& other) {
	this->moveFrom(std::move(other));
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		this->free();
		this->copyFrom(other);
	}

	return *this;
}
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		this->free();
		this->moveFrom(std::move(other));
	}

	return *this;
}
template <typename T>
Vector<T>::~Vector() {
	this->free();
}

template <typename T>
void Vector<T>::push_back(const T& element) {
	if (this->size == this->capacity) {
		this->resize();
	}

	this->data[this->size] = element;
	this->size++;
}
template <typename T>
void Vector<T>::pop_back() {
	if (this->size == 0) {
		throw std::length_error("Vector is empty!");
	}

	this->size--;
}
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
	if (index >= this->size) {
		throw std::out_of_range("Index outside the range of the array!");
	}

	return this->data[index];
}
template <typename T>
T& Vector<T>::operator[](size_t index) {
	if (index >= this->size) {
		throw std::out_of_range("Index outside the range of the array!");
	}

	return this->data[index];
}
template <typename T>
bool Vector<T>::empty() const {
	return this->size == 0;
}
template <typename T>
size_t Vector<T>::size() const {
	return this->size;
}
template <typename T>
size_t Vector<T>::capacity() const {
	return this->capacity;
}
template <typename T>
void Vector<T>::clear() {
	this->size = 0;
}