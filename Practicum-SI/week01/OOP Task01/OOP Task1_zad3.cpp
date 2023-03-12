#include <iostream>

const int MAX_ARR = 5;

struct OrderPair
{
    int first;
    int second;
};

void InputOrderPair(OrderPair& orderPair)
{
    std::cin >> orderPair.first;
    std::cin >> orderPair.second;
}

void OutputOrderPair(const OrderPair& orderPair)
{
    std::cout << orderPair.first << " " << orderPair.second << std::endl;
}

bool BiggerOrderPair(const OrderPair& pOne, const OrderPair& pTwo)
{
    if ((pOne.first > pTwo.first) || ((pOne.first == pTwo.first && pOne.second > pTwo.second)))
        return 0;
    return 1;
}

void SwapVar(OrderPair* arr, int j, OrderPair temp = { 0,0 })
{
    temp = arr[j - 1];
    arr[j - 1] = arr[j];
    arr[j] = temp;
}

void ChekingForSwap(OrderPair* arr, int j)
{
    if (BiggerOrderPair(arr[j - 1], arr[j]))
    {
        SwapVar(arr, j);
    }
}

void BubbleSort(OrderPair* arr)
{
    for (int i = 1; i < MAX_ARR; i++)
    {
        for (int j = 1; j < MAX_ARR; j++)
        {
            ChekingForSwap(arr, j);
        }
    }
}

void BiggestOrderPair(OrderPair* arr)
{
    BubbleSort(arr);
    OutputOrderPair(arr[0]);
}

void OutputOrderPairArray(OrderPair* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "(" << arr[i].first << " " << arr[i].second << ")" << std::endl;
    }
}

void InputOrderPair(OrderPair* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i].first >> arr[i].second;
    }
}

void SortOrderPairDynamicArray(OrderPair* arr, int n)
{
    InputOrderPair(arr, n);
    BubbleSort(arr);
    OutputOrderPairArray(arr, n);
}

int main()
{
    //OrderPair arr[MAX_ARR] = { 1,2,4,5,1,5,6,7,3,3 };
    //BiggestOrderPair(arr);

    int n = 0;
    std::cin >> n;
    OrderPair* arr = new OrderPair[n];
    SortOrderPairDynamicArray(arr, n);
}
