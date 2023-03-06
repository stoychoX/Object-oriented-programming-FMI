#include <iostream>
#include <fstream>

void SaveToFile(const int& a, const int& b, const int& c, const char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return;
	}
	ofs << (a + b + c) << std::endl << (a * b * c);
	ofs.close();
}

int GetDiff(const char* fileName)
{
	std::ifstream ifs(fileName);
	int sum, mult;
	ifs >> sum;
	ifs.ignore();
	ifs >> mult;
	ifs.close();
	return abs(sum - mult);
}

int main()
{
	int a, b, c;
	std::cin >> a >> b >> c;
	SaveToFile(a,b,c,"File.txt");
	std::cout << GetDiff("File.txt");
}
