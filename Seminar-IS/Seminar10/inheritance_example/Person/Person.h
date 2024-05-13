#pragma once
class Person
{
private:
	char* name;
	unsigned age;

	void free();
	void copyFrom(const Person&);
	void move(Person&&);

	void setName(const char* oldName);
public:
	Person();
	Person(const char* name, unsigned age);

	Person(const Person&);
	Person(Person&&);

	Person& operator=(const Person&);
	Person& operator=(Person&&);

	const char* getName() const;
	unsigned getAge() const;

	~Person();
};

