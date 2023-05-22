#pragma once
#include <stdexcept>
template <typename T>
class vector {
public:
	vector();
	vector(size_t n, const T& elem);
	
	vector(const vector<T>& other);
	vector<T>& operator=(const vector<T>& other);
	
	vector(vector<T>&& other);
	vector<T>& operator=(vector<T>&& other);
	
	void push_back(const T& elem);
	void push_back(T&& elem);
	void pop_back();
	const T& operator[](size_t at) const;
	T& operator[](size_t at);
	bool isEmpty() const;
	size_t mySize() const;
	size_t myCapacity() const;
	void clear(); 

	~vector();
private:
	T* data;
	size_t size;
	size_t capacity;
	void copyFrom(const vector<T>& other);
	void moveFrom(vector<T>&& other);
	void free();
	void resize();
};
template <typename T>
vector<T>::vector() {
	this->capacity = 8;
	this->size = 0;
	this->data = new T[capacity];
}

template <typename T>
vector<T>::vector(size_t n, const T& elem)
{
	this->size = n;
	this->capacity = n;
	this->data = new T[n];
	for (int i = 0; i < size; i++) {
		this->data[i] = elem;
	}
}

template <typename T>
vector<T>::vector(const vector<T>& other) {
	copyFrom(other);
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
vector<T>::vector(vector<T>&& other) {
	moveFrom(std::move(other));
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
vector<T>::~vector() {
	free();
}

template <typename T>
void vector<T>::copyFrom(const vector<T>& other) {
	this->data = new T[other.capacity];
	for (int i = 0; i < other.capacity; i++) {
		this->data[i] = other.data[i];
	}
	this->capacity = other.capacity;
	this->size = other.size;
}

template <typename T>
void vector<T>::moveFrom(vector<T>&& other) {
	this->size = other.size;
	this->capacity = other.capacity;
	this->data = other.data;
	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
void vector<T>::free() {
	delete[] data;
	data = nullptr;
}

template <typename T>
void vector<T>::resize() {
	T* resizedData = new T[capacity * 2];
	for (size_t i = 0; i < size; i++) {
		resizedData[i] = data[i];
	}
	capacity *= 2;
	free();
	data = resizedData;
}

template <typename T>
void vector<T>::push_back(const T& elem) {
	if (size == capacity)
		resize();
	this->data[size] = elem;
	size++;
}

template <typename T>
void vector<T>::push_back(T&& elem) {
	if (size == capacity)
		resize();
	data[size] = std::move(elem);// move op=
	size++;
}

template <typename T>
void vector<T>::pop_back() {
	if (isEmpty())
		throw std::logic_error("Empty vector!");
	size--;
}

template <typename T>
const T& vector<T>::operator[](size_t at) const {
	if (at >= capacity) {
		throw std::out_of_range("violation!!!");
	}
	return this->data[at];
}

template <typename T>
T& vector<T>::operator[](size_t at) {
	if (at >= capacity) {
		throw std::out_of_range("violation!!!");
	}
	return this->data[at];
}

template <typename T>
bool vector<T>::isEmpty() const {
	return size == 0;
}

template <typename T>
size_t vector<T>::mySize() const {
	return size;
}

template <typename T>
size_t vector<T>::myCapacity() const {
	return capacity;
}

template <typename T>
void vector<T>::clear() {
	free();
	size = 0;
}