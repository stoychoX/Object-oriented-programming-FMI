#pragma once

class Vector {
private:

	int* data = nullptr;
	size_t size = 0;
	size_t capacity;
	
	void resize(size_t newCapacity);

	void assertIndex(size_t index) const;
	void upsizeIfNeeded();
	void downsizeIfNeeded();

public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector& other);
	Vector(Vector&& other) noexcept;
	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other) noexcept;
	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	void pushBack(int element);
	void pushAt(int element, size_t index);
	int popBack();
	int popAt(size_t index);

	bool empty() const;
	void clear();
	void shrinkToFit();

	int& operator[](size_t index);
	const int& operator[](size_t index) const;

private:
	void copyFrom(const Vector& other);
	void moveFrom(Vector&& other) noexcept;
	void free();
};
