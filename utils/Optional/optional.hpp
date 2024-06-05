#pragma once
#include <stdexcept>

template<class T>
class Optional
{
private:
	T* data = nullptr;

	void free();
	void copyFrom(const Optional&);

public:
	Optional() = default;
	Optional(const T&);

	Optional(const Optional&);
	Optional& operator=(const Optional&);

	const T& operator*() const;
	T& operator*();

	operator bool() const;

	const T& value() const;

	bool has_value() const;
	const T& value_or(const T&) const;

	void reset();

	~Optional();
};

template<class T>
void Optional<T>::free()
{
	delete data;
	data = nullptr;
}

template<class T>
void Optional<T>::copyFrom(const Optional& val)
{
	if (val.has_value())
		data = new T(*val.data);
	else
		data = nullptr;
}

template<class T>
Optional<T>::Optional(const T& arg) : data(new T(arg)) {}

template<class T>
Optional<T>::Optional(const Optional& other)
{
	copyFrom(other);
}

template<class T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
const T& Optional<T>::operator*() const
{
	if (!has_value())
		throw std::runtime_error("No value");
	return *data;
}

template<class T>
T& Optional<T>::operator*()
{
	if (!has_value())
		throw std::runtime_error("No value");
	return *data;
}

template<class T>
Optional<T>::operator bool() const
{
	return has_value();
}

template<class T>
const T& Optional<T>::value() const
{
	if (!has_value())
		throw std::runtime_error("No value");
	return *data;
}

template<class T>
bool Optional<T>::has_value() const
{
	return data != nullptr;
}

template<class T>
const T& Optional<T>::value_or(const T& arg) const
{
	if (has_value())
		return *data;
	return arg;
}

template<class T>
void Optional<T>::reset()
{
	free();
}

template<class T>
Optional<T>::~Optional()
{
	free();
}
