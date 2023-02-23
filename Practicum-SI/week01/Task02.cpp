//#include <iostream>
//
//int numberOfIntegersAbove(char ch, int N, int* myArr)
//{
//	if (myArr == nullptr)
//	{
//		return 0;
//	}
//	int counter = 0;
//	for (int i = 0; i < N; i++)
//	{
//		if (myArr[i] > ch)
//		{
//			counter++;
//		}
//	}
//	return counter;
//}
//
//int main()
//{
//	int N = 0;
//	std::cin >> N;
//	int* intArr = new int[N];
//	for (int i = 0; i < N; i++)
//	{
//		std::cin >> intArr[i];
//	}
//	char ch;
//	std::cin >> ch;
//	std::cout << numberOfIntegersAbove(ch, N, intArr);
//	delete[] intArr;
//}