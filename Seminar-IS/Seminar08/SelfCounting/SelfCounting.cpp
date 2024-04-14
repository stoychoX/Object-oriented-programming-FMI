#include "SelfCounting.h"

//static class member's should be
//initialized here ( "only in one .cpp" )
unsigned SelfCounting::aliveObjectsCount = 0;
unsigned SelfCounting::createdCount = 0;

SelfCounting::SelfCounting()
{
    ++aliveObjectsCount;
    ++createdCount;
}

SelfCounting::SelfCounting(const SelfCounting& other)
{
	aliveObjectsCount++;
	createdCount++;
}

SelfCounting::~SelfCounting()
{
	aliveObjectsCount--;
}

unsigned SelfCounting::getAliveObjectsCount()
{
	return aliveObjectsCount;
}

unsigned SelfCounting::getCreatedCount()
{
	return createdCount;
}