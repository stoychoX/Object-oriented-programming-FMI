#pragma once
#include <vector>

struct Criteria
{
	bool operator()(const std::vector<int>& setNumbers, int element) const
	{
		for (size_t i = 0; i < setNumbers.size(); i++)
		{
			for (size_t j = i + 1; j < setNumbers.size(); j++)
			{
				if (setNumbers[i] + setNumbers[j] == element) 
				{
					return true;
				}
			}
		}

		return false;
	}
};