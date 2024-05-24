#include <iostream>
#include "Queue.hpp"

int main()
{
	Queue<int> q;

	for (size_t i = 0; i < 100; i++)
	{
		q.push(i);
	}

	Queue<int> qCopy = q;

	while (!qCopy.empty())
	{
		std::cout << qCopy.top() << " ";
		qCopy.pop();
	}
}