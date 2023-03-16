#include <iostream>
#include <fstream>
#include <string>

struct JobOffer
{
	char firmName[25]{};
	size_t programmersCount;
	size_t daysOffCount;
	double salary;
};

void ReadJobOffersFromConsole(JobOffer& offer)
{
	std::cin.getline((char*)offer.firmName, 25);
	std::cin >> offer.programmersCount;
	std::cin >> offer.daysOffCount;
	std::cin >> offer.salary;
	std::cin.ignore();
}

void SaveToFile(std::ofstream& ofs, const JobOffer* offers, int n)
{
	if (!ofs.is_open())
	{
		std::cout << "Error!";
		return;
	}
	
	ofs.write((const char*)offers, n * sizeof(JobOffer));
}

size_t getFileSize(std::ifstream& ifs)
{
    size_t currentPosition = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    ifs.seekg(currentPosition);
    return fileSize;
}

JobOffer* filterOffer(std::ifstream& ifs, size_t minSalary, int& filteredOffersCount)
{
	int n = getFileSize(ifs) / sizeof(JobOffer);
	JobOffer* offers = new JobOffer[n];
	if (!ifs.is_open())
	{
		return nullptr;
	}

	filteredOffersCount = 0;
	for(int i = 0; i < n; i++)
	{
		JobOffer buffJobOffer;
		ifs.read((char*)& buffJobOffer, sizeof(JobOffer));
		if (buffJobOffer.salary >= minSalary)
		{
			offers[filteredOffersCount] = buffJobOffer;
			filteredOffersCount++;
		}
	}
	ifs.seekg(0);
	return offers;
}
JobOffer findOffer(std::ifstream& ifs, const char* name)
{
	JobOffer error{"error", 0, 0, 0};
	if (!ifs.is_open())
	{
		return error;
	}
	int n = getFileSize(ifs) / sizeof(JobOffer);
	JobOffer offer;
	for (int i = 0; i < n; i++)
	{
		ifs.read((char*)&offer, sizeof(JobOffer));
		if (strcmp(offer.firmName, name) == 0)
		{
			ifs.seekg(0);
			return offer;
		}
	}
}
void print(const JobOffer& offer)
{
	std::cout << offer.firmName << " " << offer.programmersCount << " " << offer.daysOffCount << " " << offer.salary << std::endl;
}
int main()
{
	int n;
	std::cin >> n;
	std::cin.ignore();
	JobOffer* offers = new JobOffer[n];
	for (size_t i = 0; i < n; i++)
	{
		ReadJobOffersFromConsole(offers[i]);
	}
	char fileName[1024];
	std::cin.getline(fileName, 1024);
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary | std::ios::app);
	SaveToFile(ofs, offers, n);
	ofs.close();

	
	size_t minSalary;
	std::cin >> minSalary;
	std::cin.ignore();
	int filteredOffersCount;
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
	JobOffer* filteredOffers = filterOffer(ifs, minSalary, filteredOffersCount);
	if (filteredOffersCount == 0)
	{
		std::cout << "No offers found";
	}
	for (size_t i = 0; i < filteredOffersCount; i++)
	{
		print(filteredOffers[i]);
	}
	char name[25];
	std::cin.getline(name, 25);
	print(findOffer(ifs, name));
	delete[] filteredOffers;
	ifs.close();
	delete[] offers;
}