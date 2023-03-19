#include <iostream>
#include <fstream>

struct Ad {
	char name[10];
	unsigned countProgrammers;
	unsigned countFreeDays;
	double salary;
};

Ad readAdFromConsole()
{
	Ad ad;
	std::cin >> ad.name;
	std::cin >> ad.countProgrammers;
	std::cin >> ad.countFreeDays;
	std::cin >> ad.salary;
	return ad;
}

void saveAdIntoBinary(std::ofstream& ofs, Ad& ad)
{
	if (!ofs.is_open())
	{
		return;
	}
	//ofs.write((const char*)&ad, sizeof(ad));
	ofs.write(ad.name, 10);
	ofs.write((const char*)&ad.countProgrammers, sizeof(ad.countProgrammers));
	ofs.write((const char*)&ad.countFreeDays, sizeof(ad.countFreeDays));
	ofs.write((const char*)&ad.salary, sizeof(ad.salary));
}

void saveAdsIntoBinaryFile(std::ofstream& ofs, Ad* ads, unsigned count)
{
	if (!ofs.is_open())
	{
		return;
	}
	for (size_t i = 0; i < count; i++)
	{
		saveAdIntoBinary(ofs, ads[i]);
	}
}

void printAd(const Ad& ad)
{
	std::cout << "Name: " << ad.name << std::endl;
	std::cout << "Count workers: " << ad.countProgrammers << std::endl;
	std::cout << "Free days: " << ad.countFreeDays << std::endl;
	std::cout << "Salary: " << ad.salary << " .lv" << std::endl;
}

size_t getFileSize(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		return  0;
	}
	unsigned currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	unsigned size = ifs.tellg();
	ifs.seekg(currPos);
	ifs.clear();
	return size;
}

Ad readAdFromBinary(std::ifstream& ifs)
{
	Ad ad{ "Err",0,0,0 };
	if (!ifs.is_open())
	{
		return ad;
	}
	ifs.read(ad.name, 10);
	ifs.read((char*)&ad.countProgrammers, sizeof(ad.countProgrammers));
	ifs.read((char*)&ad.countFreeDays, sizeof(ad.countFreeDays));
	ifs.read((char*)&ad.salary, sizeof(ad.salary));
	return ad;
}

void filterOffer(std::ifstream& ifs, size_t minSalary, unsigned countAds)
{
	if (!ifs.is_open())
	{
		return;
	}
	unsigned currPos = ifs.tellg();
	for (size_t i = 0; i < countAds; i++)
	{
		Ad ad = readAdFromBinary(ifs);
		if (ad.salary >= minSalary)
		{
			printAd(ad);
		}
	}
	ifs.seekg(currPos);
	ifs.clear();
}

void findOffer(std::ifstream& ifs, const char* name, unsigned countAds)
{
	if (!ifs.is_open())
	{
		return;
	}
	unsigned currPos = ifs.tellg();
	for (size_t i = 0; i < countAds; i++)
	{
		Ad ad = readAdFromBinary(ifs);
		if (strcmp(name, ad.name) == 0)
		{
			printAd(ad);
		}
	}
	ifs.seekg(currPos);
	ifs.clear();
}

int main()
{
	unsigned n;
	std::cin >> n;
	Ad* ads = new Ad[n];
	for (size_t i = 0; i < n; i++)
	{
		ads[i] = readAdFromConsole();
	}
	std::ofstream ofs("AdsList.txt", std::ios::binary | std::ios::ate);
	if (!ofs.is_open())
	{
		delete[] ads;
		return -1;
	}
	saveAdsIntoBinaryFile(ofs, ads, n);
	delete[] ads;
	ofs.close();

	std::ifstream ifs("AdsList.txt", std::ios::binary);
	if (!ifs.is_open())
	{
		return -1;
	}
	
	//why when we save Ad to a file he padding is not there so the sizeof Ad is not the same as the original
	std::cout << "Ads from Google: " << std::endl;
	findOffer(ifs, "Google", n);

	std::cout << std::endl;

	std::cout << "Salary over 1000 lv.: " << std::endl;
	filterOffer(ifs, 1000, n);

	//input
	/*3
	ABM
	4
	5
	1000
	Google
	44
	33
	3000
	Google
	3
	3
	800*/
}
