#include <iostream>
#include <fstream>
#pragma warning(disable : 4996);
const size_t MAX_SIZE = 25;

struct Company
{
    char companyName[MAX_SIZE];
    size_t countProgrammers;
    size_t countDays;
    size_t salary;
};

Company *getJobOffers(size_t &n)
{
    std::cin >> n;
    Company *jobOffers = new Company[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> jobOffers[i].companyName;
        std::cin.ignore();
        std::cin >> jobOffers[i].countProgrammers;
        std::cin >> jobOffers[i].countDays;
        std::cin >> jobOffers[i].salary;
    }
    return jobOffers;
}

void saveOffersToFile(std::ofstream &ofs, const Company *jobOffers, size_t n)
{
    ofs.write((char *)jobOffers, n * sizeof(Company));
}

size_t getFileSize(std::ifstream &ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t fileSize = ifs.tellg();
    ifs.seekg(currentPos);
    return fileSize;
}
Company *getJobOffersFromFile(std::ifstream &ifs, size_t countOffersFromFile)
{
    size_t currentPos = ifs.tellg();
    Company *jobOffersFromFile = new Company[countOffersFromFile];
    ifs.read((char *)jobOffersFromFile, countOffersFromFile);
    ifs.seekg(currentPos);
    return jobOffersFromFile;
}

void filterOffer(const char *filePath, size_t minSalary)
{
    std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cout << "Error while opening file!";
        return;
    }
    size_t countOffersInFile = getFileSize(ifs) / sizeof(Company);
    Company *jobOffersFromFile = getJobOffersFromFile(ifs, countOffersInFile);
    for (size_t i = 0; i < countOffersInFile; i++)
    {
        if (jobOffersFromFile[i].salary > minSalary)
        {
            std::cout << "Name of the company: " << jobOffersFromFile[i].companyName << std::endl;
            std::cout << "The number of programmers in that company is:: " << jobOffersFromFile[i].countProgrammers << std::endl;
            std::cout << "The number of days with paid leave is: " << jobOffersFromFile[i].countDays << std::endl;
            std::cout << "The salary the employees in this company receive is: " << jobOffersFromFile[i].salary;
        }
    }
    delete[] jobOffersFromFile;
    ifs.close();
}

bool findOffer(const char *filePath, const char *name)
{
    std::ifstream ifs(filePath, std::ios::in | std::ios::binary);

    if (!ifs.is_open())
    {
        std::cout << "Error while opening file!";
        return;
    }
    size_t countOffersInFile = getFileSize(ifs) / sizeof(Company);
    Company *jobOffersFromFile = getJobOffersFromFile(ifs, countOffersInFile);
    ifs.close();
    for (size_t i = 0; i < countOffersInFile; i++)
    {
        return (strcmp(jobOffersFromFile[i].companyName, name) == 0);
    }
    return false;
}

int main()
{
    std::ofstream ofs("joboffers.txt", std::ios::binary | std::ios::app);
    if (!ofs.is_open())
    {
        std::cout << "Error while opening file!";
        return 0;
    }
    size_t n;
    Company *jobOffers = getJobOffers(n);
    saveOffersToFile(ofs, jobOffers, n);
    filterOffer("joboffers.txt", 2000);
    if (findOffer)
    {
        std::cout << "Job offer exists.";
    }
    else
    {
        std::cout << "Job offer does not exist.";
    }
    ofs.close();
    delete[] jobOffers;
    return 0;
}
