#include "Random.h"

size_t Random::seed = 0; 
Random Random::instance;

size_t Random::getRand() const {
	seed = (1103515245 * seed + 12345) % (1ull << 31);
	return seed;
}

void Random::setSeed(size_t s) { seed = s; }

const Random& Random::getInstance() {
	return instance;
}