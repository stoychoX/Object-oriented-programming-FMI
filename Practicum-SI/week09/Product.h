#pragma once

class Product
{
	static unsigned int nextId;
	unsigned int id;
	char* name;

	void free();
	void moveFrom(Product&& other);
public:
	Product() = default;
	Product(const char* name);
	Product(const Product& other) = delete;
	Product(Product&& other);
	Product& operator=(Product&& other);
	Product& operator=(const Product& other) = delete;
	~Product();

	void setName(const char* str);
	const char* getName() const;
	unsigned int getId() const;
};