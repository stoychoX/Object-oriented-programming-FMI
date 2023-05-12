#include "Product.h"

Product::Product(const MyString& name)
{
	setName(name);
}
const MyString& Product::getName()const
{
	return name;
}
void Product::setName(const MyString& newName)
{
	name = newName;
}