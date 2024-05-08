#pragma once
#include <fstream>

class Set
{
public:
	bool virtual operator[](int element) const = 0;
	void virtual print(std::ostream& stream) const = 0;
	virtual ~Set() = default;
};

