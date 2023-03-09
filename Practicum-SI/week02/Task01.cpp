#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

void WriteSumAndProductOfThreeNumbers()
{
	int a, b, c;
	cin >> a >> b >> c;

	ofstream ofs("result.txt", std::ios::trunc);

	ofs << "Sum: " << a + b + c << " Product: " << a * b * c << endl;

	ofs.close();
}

void ReadSumAndProductOfThreeNumbers()
{
	ifstream ifs("result.txt");

	if (!ifs.is_open())
		return;

	char buff[1024];

	ifs.getline(buff,1024);

	cout << buff;

	ifs.close();
}

int main()
{
	WriteSumAndProductOfThreeNumbers();
	ReadSumAndProductOfThreeNumbers();
}
