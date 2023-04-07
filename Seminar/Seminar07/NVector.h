#pragma once
#include<iostream>

class NVector {
private:
	int* data;
	size_t size;

public:
	NVector(size_t n);

	NVector(const NVector&);

	NVector& operator+=(const NVector&);
	NVector& operator-=(const NVector&);

	NVector& operator*=(int);

	bool operator%(const NVector&) const;

	NVector& operator=(const NVector&);

	int operator[](size_t idx) const;
	int& operator[](size_t idx);

	bool operator||(const NVector& other) const;

	double length() const;

	friend std::ostream& operator<<(std::ostream&, const NVector&);
	friend std::istream& operator>>(std::istream&, NVector&);

	~NVector();

private:
	void free();
	void copyFrom(const NVector&);
};

NVector operator+(const NVector&, const NVector&); 
NVector operator-(const NVector&, const NVector&);

NVector operator*(const NVector&, int);
NVector operator*(int, const NVector&);