#include "Engine.h"

Engine::Engine(const char* _prodName, const char* _desc, unsigned _horsePwr) : CarPart(_prodName, _desc)
{
	setHorsePwr(_horsePwr);
}

void Engine::setHorsePwr(unsigned _horsePwr)
{
	horsePwr = _horsePwr;
}
unsigned Engine::getHorsePwr() const
{
	return horsePwr;
}