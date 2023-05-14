#include "Engine.h"

Engine::Engine(size_t id, const MyString& producerName, const MyString& description,
	unsigned horsePowers) :CarPart(id, producerName, description)
{
	setHP(horsePowers);
}
unsigned Engine::getHP()const
{
	return _horsePowers;
}
void Engine::setHP(unsigned hp)
{
	_horsePowers = hp;
}
std::ostream& operator<<(std::ostream& os, const Engine& part)
{
	os << (CarPart)part << " - " << part.getHP() << " hp";
	return os;
}