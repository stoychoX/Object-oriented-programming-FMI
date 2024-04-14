#include <iostream>
#include "ImmutableString.h"

int main()
{
	ImmutableString str = "Hello";

	ImmutableString second = "World";

	ImmutableString str2 = "Hello";

	std::cout << str << " " << second << " " << str2 << std::endl;

	ImmutableString::debug();

	ImmutableString strings[] = 
	{
		"This",
		"Is",
		"Example",
		"Of",
		"How",
		"The",
		"Strings",
		"Are",
		"Kept",
		"Sorted",
		"In",
		"The",
		"String",
		"Pool",
		"This",
		"Is",
		"Example",
		"Of",
		"How",
		"The",
		"Strings",
		"Are",
		"Kept",
		"Sorted",
		"In",
		"The",
		"String",
		"Pool",
		"This",
		"Is",
		"Example",
		"Of",
		"How",
		"The",
		"Strings",
		"Are",
		"Kept",
		"Sorted",
		"In",
		"The",
		"String",
		"Pool",
		"This",
		"Is",
		"Example",
		"Of",
		"How",
		"The",
		"Strings",
		"Are",
		"Kept",
		"Sorted",
		"In",
		"The",
		"String",
		"Pool",
		"This",
		"Is",
		"Example",
		"Of",
		"How",
		"The",
		"Strings",
		"Are",
		"Kept",
		"Sorted",
		"In",
		"The",
		"String",
		"Pool", 
		"A", 
		"Z", 
		"M"
	};

	ImmutableString::debug();
}