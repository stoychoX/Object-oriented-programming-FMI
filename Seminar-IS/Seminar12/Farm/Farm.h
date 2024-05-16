#pragma once
#include "Animal.h"
#include <stddef.h>
class Farm
{
private:
	Animal** data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const Farm&);
	void move(Farm&&);

	void resize();

public:
	Farm();
	Farm(const Farm&);
	Farm(Farm&&) noexcept;

	Farm& operator=(const Farm&);
	Farm& operator=(Farm&&) noexcept;

	void addAnimal(AnimalType);
	void makeSound() const;
	AnimalType getType(size_t idx) const;

	~Farm();
};

