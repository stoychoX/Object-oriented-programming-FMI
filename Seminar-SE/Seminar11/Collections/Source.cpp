#include "Collection.h"
#include "NormalCollection.h"
#include "IntervalCollection.h"
#include "UnionSupersetOperation.h"
#include <iostream>
#include <chrono>
#include <vector>
#include "SortedCollection.h"
 
struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
 
    Timer() {
        start = std::chrono::steady_clock::now();
    }
 
    ~Timer() {
        end = std::chrono::steady_clock::now();
        duration = end - start;
        float output = duration.count() * 1.000f;
        std::cout << "executed for: " << output << " ms"<<std::endl;
    }
};

void testAdd(Collection* c, unsigned n)
{
	Timer t;

	for (size_t i = 0; i < n; i++)
	{
		c->add(rand() % 20000);
	}
}

void testRemove(Collection* c, unsigned n)
{
	Timer t;
	for (size_t i = 0; i < n; i++)
	{
		while (c->contains(i))
		{
			c->remove(i);
		}
	}
}

void testContains(Collection* c, unsigned n)
{
	Timer t;
	unsigned count = 0;
	for (size_t i = 0; i < n; i++)
	{
		if(c->contains(i))
		{
			count++;
		}
	}
	std::cout << count << std::endl;
}

void testCount(Collection* c, unsigned n)
{
	Timer t;
	unsigned count = 0;
	for (size_t i = 0; i < n; i++)
	{
		if(c->count(i))
		{
			count += c->count(i);
		}
	}
	std::cout << count << std::endl;
}

void sep()
{
	std::cout << std::endl;
	for (size_t i = 0; i < 20; i++)
	{
		std::cout << '=';
	}
	std::cout << std::endl;
}

int main()
{
	srand(time(NULL));
	unsigned load = 100000;
	Collection* n = new NormalCollection();
	Collection* i = new IntervalCollection(0, 20000);
	Collection* s = new SortedCollection();

	std::cout << "Start testing add operation..." << std::endl;
	std::cout << "Normal..." << std::endl;
	testAdd(n, load);
	std::cout << "Interval..." << std::endl;
	testAdd(i, load);
	std::cout << "Sorted..." << std::endl;
	testAdd(s, load);

	sep();

	std::cout << "Start testing contains operation..." << std::endl;
	std::cout << "Normal..." << std::endl;
	testContains(n, load);
	std::cout << "Interval..." << std::endl;
	testContains(i, load);
	std::cout << "Sorted..." << std::endl;
	testContains(s, load);

	sep();

	std::cout << "Start testing count operation..." << std::endl;
	std::cout << "Normal..." << std::endl;
	testContains(n, load);
	std::cout << "Interval..." << std::endl;
	testContains(i, load);
	std::cout << "Sorted..." << std::endl;
	testContains(s, load);

	sep();

	std::cout << "Start testing remove operation..." << std::endl;
	std::cout << "Normal..." << std::endl;
	testRemove(n, load);
	std::cout << "Interval..." << std::endl;
	testRemove(i, load);
	std::cout << "Sorted..." << std::endl;
	testRemove(s, load);

	delete n;
	delete i;
	delete s;	
}