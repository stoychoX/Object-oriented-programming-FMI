#include "NVector.h"
#include<cmath>

NVector::NVector(size_t n) : size{ n } {
	data = new int[size];
}

NVector::NVector(const NVector& other) {
	copyFrom(other);
}

NVector& NVector::operator+=(const NVector& other) {
	if (size != other.size) {
		throw "Sizes are not equal";
	}

	for (size_t i = 0; i < size; i++)
		data[i] += other.data[i];

	return *this;
}

NVector& NVector::operator-=(const NVector& other) {
	if (size != other.size) {
		throw "Sizes are not equal";
	}

	for (size_t i = 0; i < size; i++)
		data[i] -= other.data[i];

	return *this;
}

NVector& NVector::operator*=(int scalar) {
	for (size_t i = 0; i < size; i++)
		data[i] *= scalar;

	return *this;
}

bool NVector::operator%(const NVector& other) const {
	if (size != other.size) {
		throw "Sizes are not equal";
	}

	int ans = 0;

	for (size_t i = 0; i < size; i++)
		ans += data[i] * other.data[i];
	
	return (ans == 0);
}

NVector& NVector::operator=(const NVector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

int NVector::operator[](size_t idx) const {
	if (idx >= size)
		throw "Out of range";

	return data[idx];
}

int& NVector::operator[](size_t idx) {
	if (idx >= size)
		throw "Out of range";

	return data[idx];
}

bool NVector::operator||(const NVector& other) const {
	if (size != other.size) {
		throw "Sizes not equal";
	}

	double lambda = 0;
	bool foundIndex = false;

	for (size_t i = 0; i < size; i++) {
		if (data[i] && other.data[i]) {
			if (foundIndex == false) {
				lambda = (double)data[i] / other.data[i];
				foundIndex = true;
			}
			else if ((double)data[i] / (double)other.data[i] != lambda) {
				return false;
			}
		}
		else if ((data[i] == 0) ^ (other.data[i] == 0)) {
			return false;
		}
	}

	return true;
}

double NVector::length() const {
	size_t toreturn = 0;

	for (size_t i = 0; i < size; i++)
		toreturn += data[i] * data[i];

	return sqrt(toreturn);
}

NVector::~NVector() {
	free();
}

void NVector::free() {
	delete[] data;
	data = nullptr;
}

void NVector::copyFrom(const NVector& other) {
	size = other.size;
	data = new int[size];

	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

std::ostream& operator<<(std::ostream& ofs, const NVector& arg) {
	for (size_t i = 0; i < arg.size; i++)
		ofs << arg.data[i] << " ";
	
	ofs << std::endl;

	return ofs;
}

std::istream& operator>>(std::istream& ifs, NVector& arg) {
	for (size_t i = 0; i < arg.size; i++)
		ifs >> arg.data[i];

	return ifs;
}

NVector operator+(const NVector& lhs, const NVector& rhs) {
	NVector toReturn(lhs);
	toReturn += rhs;

	return toReturn;
}

NVector operator-(const NVector& lhs, const NVector& rhs) {
	NVector toReturn(lhs);
	toReturn -= rhs;

	return toReturn;
}

NVector operator*(const NVector& arg, int scalar) {
	NVector toReturn(arg);
	toReturn *= scalar;

	return toReturn;
}

NVector operator*(int scalar, const NVector& arg) {
	return arg * scalar;
}
