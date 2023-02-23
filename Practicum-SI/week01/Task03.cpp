#include <iostream>

const int MAX_COUPLES = 100;

struct Nums
{
	int first = 0;
	int second = 0;
};

void getValues(Nums& couple)
{
	std::cin >> couple.first;
	std::cin >> couple.second;
}

void printNums(const Nums& couple)
{
	std::cout << couple.first << " ";
	std::cout << couple.second;
}

int compareCouples(const Nums& coupleOne, const Nums& coupleTwo)
{
	if ((coupleOne.first > coupleTwo.first) || ((coupleOne.first == coupleTwo.first) && (coupleOne.second > coupleTwo.second)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void swap(Nums& couple1, Nums& couple2)
{
	Nums temp = couple1;
	couple1 = couple2;
	couple2 = temp;
}

Nums returnHighestCouple(Nums* myArr)
{
	Nums maxCouple = myArr[0];
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			if (compareCouples(myArr[i], myArr[j]) == 1)
			{
				swap(myArr[i], myArr[j]);
			}
			maxCouple = myArr[j];
		}
	}
	return maxCouple;
}

void sortCouples(Nums* myArr, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (compareCouples(myArr[i], myArr[j]) == 1)
			{
				swap(myArr[i], myArr[j]);
			}
		}
	}
}

void PrintCouples(Nums* myArr, int length)
{
	for (int i = 0; i < length; i++)
	{
		printNums(myArr[i]);
	}
}

int main()
{
	//Nums coupleOne;
	//Nums coupleTwo;
	//getValues(coupleOne);
	//getValues(coupleTwo);
	//returnLowerCouple(coupleOne, coupleTwo);
	/*Nums couples[MAX_COUPLES];
	for (int i = 0; i < 3; i++)
	{
		getValues(couples[i]);
	}
	Nums highestCouple = returnHighestCouple(couples);
	printNums(highestCouple);*/
	int N = 0;
	std::cin >> N;
	Nums* myArr = new Nums[N];
	for (int i = 0; i < N; i++)
	{
		getValues(myArr[i]);
	}
	sortCouples(myArr, N);
	PrintCouples(myArr, N);
}