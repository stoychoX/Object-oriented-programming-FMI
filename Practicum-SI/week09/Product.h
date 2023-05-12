#pragma once
#include "MyString.h"
#pragma warning(disable:4996)
class Product
{
	MyString name;
	//TODO: some other data like desc
public:
	Product(const MyString& name);
	const MyString& getName()const;
	void setName(const MyString& newName);
};