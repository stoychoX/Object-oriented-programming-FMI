#pragma once

class SelfCounting
{
	static unsigned aliveObjectsCount;
	static unsigned createdCount;

public:
	SelfCounting();
	SelfCounting(const SelfCounting& other);
	~SelfCounting();

	static unsigned getAliveObjectsCount();
	static unsigned getCreatedCount();
};