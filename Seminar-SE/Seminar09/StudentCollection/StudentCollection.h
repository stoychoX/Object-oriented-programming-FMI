#pragma once
#include "Student.h"

class StudentCollection
{
private:
	Student** data;
	size_t size;
	size_t capacity;
	
	void free();
	void copyFrom(const StudentCollection& other);
	void move(StudentCollection&&);

	void resize(size_t newCap);

	size_t getLastFreeIndex() const;
public:
	StudentCollection();

	StudentCollection(const StudentCollection&);
	StudentCollection& operator=(const StudentCollection&);

	void pushAt(size_t idx, const Student&);
	void pushAt(size_t idx, Student&&);

	void push(const Student&);
	void push(Student&&);

	void removeAt(size_t idx);

	bool contains(size_t idx) const;

    size_t getSize() const;
    size_t getCapacity() const;

	const Student& at(size_t idx) const;

	StudentCollection& operator=(StudentCollection&&) noexcept;
	StudentCollection(StudentCollection&&) noexcept;

	~StudentCollection();
};