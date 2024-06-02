#pragma once
#include <utility>
#include <stdexcept>

template<class T>
class polymorphic_ptr
{
private:
	T* ptr = nullptr;

	void free();
	void copyFrom(const polymorphic_ptr&);
	void move(polymorphic_ptr&&);

public:
	polymorphic_ptr() = default;

	polymorphic_ptr(T*);

	polymorphic_ptr(const polymorphic_ptr&);
	polymorphic_ptr(polymorphic_ptr&&) noexcept;

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	operator bool() const;

	T* get();
	const T* get() const;

	void reset();
	void reset(T*);

	polymorphic_ptr& operator=(const polymorphic_ptr&);
	polymorphic_ptr& operator=(polymorphic_ptr&&) noexcept;

	~polymorphic_ptr();
};

template<class T>
void polymorphic_ptr<T>::free()
{
	delete ptr;
	ptr = nullptr;
}

template<class T>
void polymorphic_ptr<T>::copyFrom(const polymorphic_ptr& other)
{
	ptr = other ? other.ptr->clone() : nullptr;
}

template<class T>
void polymorphic_ptr<T>::move(polymorphic_ptr&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

template<class T>
polymorphic_ptr<T>::polymorphic_ptr(T* p) : ptr(p) {}

template<class T>
polymorphic_ptr<T>::polymorphic_ptr(const polymorphic_ptr& other)
{
	copyFrom(other);
}

template<class T>
polymorphic_ptr<T>::polymorphic_ptr(polymorphic_ptr&& other) noexcept
{
	move(std::move(other));
}

template<class T>
T* polymorphic_ptr<T>::operator->()
{
	return ptr;
}

template<class T>
const T* polymorphic_ptr<T>::operator->() const
{
	return ptr;
}

template<class T>
T& polymorphic_ptr<T>::operator*()
{
	if (get())
		return *ptr;
	throw std::runtime_error("Cannot get");
}

template<class T>
const T& polymorphic_ptr<T>::operator*() const
{
	if (get())
		return *ptr;
	throw std::runtime_error("Cannot get");
}

template<class T>
polymorphic_ptr<T>::operator bool() const
{
	return (ptr != nullptr);
}

template<class T>
T* polymorphic_ptr<T>::get()
{
	return ptr;
}

template<class T>
const T* polymorphic_ptr<T>::get() const
{
	return ptr;
}

template<class T>
void polymorphic_ptr<T>::reset()
{
	free();
}

template<class T>
void polymorphic_ptr<T>::reset(T* p)
{
	free();
	ptr = p;
}

template<class T>
polymorphic_ptr<T>& polymorphic_ptr<T>::operator=(const polymorphic_ptr& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
polymorphic_ptr<T>& polymorphic_ptr<T>::operator=(polymorphic_ptr&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template<class T>
polymorphic_ptr<T>::~polymorphic_ptr()
{
	free();
}
