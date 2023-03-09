#include <iostream>

struct CoupleNums {
	int first = INT32_MIN;
	int second = INT32_MIN;
};

void GetCouple(CoupleNums& couple)
{
	//or create new here and return it
	std::cin >> couple.first;
	std::cin >> couple.second;
}

int Compare(const CoupleNums& couple1, const CoupleNums& couple2)
{
	if (couple1.first > couple2.second || ((couple1.first == couple2.first) && couple1.second > couple2.second))
	{
		return 1;
	}
	if (couple1.first == couple2.first && couple1.second == couple2.second)
	{
		return 0;
	}
	return -1;
}

const int LEN_COUPLES_ARR = 100;
CoupleNums GetMaxCouple(CoupleNums couples[LEN_COUPLES_ARR])
{
	CoupleNums maxCouple = couples[0];
	for (int i = 1; i < LEN_COUPLES_ARR; i++)
	{
		if (Compare(couples[i], maxCouple) == 1)
		{
			maxCouple = couples[i];
		}
	}
	return maxCouple;
}

int GetIndexMinCoupleInInterval(CoupleNums* couples, int len, int startIndex)
{
	int minCoupleIndex = startIndex;
	for (int i = startIndex + 1; i < len; i++)
	{
		if (Compare(couples[minCoupleIndex], couples[i]) == 1)
		{
			minCoupleIndex = i;
		}
	}
	return minCoupleIndex;
}

void Swap(CoupleNums& couple1, CoupleNums& couple2)
{
	CoupleNums tmp = couple1;
	couple1 = couple2;
	couple2 = tmp;
}

void SortCouples(CoupleNums* couples, int len)
{
	for (int i = 0; i < len; i++)
	{
		int indexMinCouple = GetIndexMinCoupleInInterval(couples, len, i);
		Swap(couples[i], couples[indexMinCouple]);
	}
}

void PrintCouples(CoupleNums* couples, int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << couples[i].first << " " << couples[i].second << std::endl;
	}
}

int main()
{
	const int LEN = 100;
	//CoupleNums* couples = new CoupleNums[LEN];
	CoupleNums couples[LEN];
	for (int i = 0; i < 3; i++)
	{
		CoupleNums couple;
		GetCouple(couple);
		couples[i] = couple;
	}
	//SortCouples(couples, LEN);
	//PrintCouples(couples, LEN);
	CoupleNums maxCouple = GetMaxCouple(couples);
	std::cout << maxCouple.first << " " << maxCouple.second;

}

