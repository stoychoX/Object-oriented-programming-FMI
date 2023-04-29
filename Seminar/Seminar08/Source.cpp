#include<iostream>
#include"StringPool.h"

int main() {
	StringPool str(5);

	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("z");
	str.insert("y");
	str.insert("a");
	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("A");
	str.insert("c");
	str.insert("z");
	str.insert("z");
	str.insert("z");

	for (size_t i = 0; i < str.mSize(); i++) {
		std::cout << str[i].getString() << " ";
	}
}