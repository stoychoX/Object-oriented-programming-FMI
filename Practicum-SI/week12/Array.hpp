#pragma once

template <typename T, size_t S>
class Array
{
	T arr[S]{};
public:
	Array() = default;
	size_t size() const
	{
		return S;
	}
	bool empty() const
	{
		return S == 0;
	}
	void fill(const T& el)
	{
		for (size_t i = 0; i < S; i++)
		{
			arr[i] = el;
		}
	}
	const T& operator[](size_t ind) const
	{
		return arr[ind];
	}
	T& operator[](size_t ind)
	{
		return arr[ind];
	}
};