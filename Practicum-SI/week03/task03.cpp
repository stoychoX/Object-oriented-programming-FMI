#include <iostream>
#include <fstream>
#include <cstring>

const char FILE_PATH[] = "file.dat";

struct JobOffer {
    char company[26];
    int employees;
    short yearlyPaidLeave;
    double salary;
};

void readJobOffer(JobOffer& offer) {
    offer = JobOffer{};
    std::cin.getline(offer.company, 26);
    std::cin >> offer.employees >> offer.yearlyPaidLeave >> offer.salary;
    std::cin.ignore(1);
}

void printJobOffer(const JobOffer& offer) {
    std::cout << "Job Offer from: " << offer.company << std::endl;
    std::cout << "Employees: " << offer.employees << std::endl;
    std::cout << "Paid leave: " << offer.yearlyPaidLeave << "  Salary: " << offer.salary << std::endl;
    std::cout << std::endl;
}

bool addJobOffers(const char* filePath) {
    size_t n;
    std::cout << "Enter count: ";
    std::cin >> n;
    std::cin.ignore(1);

    JobOffer* offers = new JobOffer[n];
    for (size_t i = 0; i < n; i++) {
        std::cout << "Enter data for item #" << (i+1) << std::endl;
        readJobOffer(offers[i]);
    }

    size_t count = 0, eof = 0;

    std::ifstream input(filePath, std::ios::in | std::ios::binary);
    if (input.is_open()) {
        input.read((char*)&count, sizeof(count));
        input.seekg(0, std::ios::end);
        eof = input.tellg();
        input.close();
    }

    std::ofstream output;
    output.open(filePath, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    if (!output.is_open()) {
        output.open(filePath, std::ios::out | std::ios::binary);
        if (!output.is_open()) {
            return false;
        }
    }

    count += n;
    output.seekp(0, std::ios::beg);
    output.write((const char*)&(count), sizeof((count)));
    if(eof != 0) {
        output.seekp(eof, std::ios::beg);
    }
    std::cout << "End is at: " << output.tellp() << std::endl;

    for (int i = 0; i < n; i++) {
        output.write((const char*)&offers[i], sizeof(offers[i]));
    }

    output.close();
    return true;
}

bool filterOffer(const char* filePath, size_t minSalary) {
    std::ifstream input(filePath, std::ios::in | std::ios::binary);
    if(!input.is_open()) {
        return false;
    }

    size_t count = 0;
    JobOffer buffer{};
    input.read((char *)&count, sizeof(count));
    while(count-- ) {
        input.read((char *)&buffer, sizeof(buffer));
        if(buffer.salary > (double)minSalary) {
            printJobOffer(buffer);
        }
    }

    input.close();
    return true;
}

JobOffer* findOffer(const char* filePath, const char* name) {
    std::ifstream input(filePath, std::ios::in | std::ios::binary);
    if(!input.is_open()) {
        return nullptr;
    }

    size_t count = 0;
    JobOffer buffer{};
    input.read((char *)&count, sizeof(count));
    while(count-- ) {
        input.read((char *)&buffer, sizeof(buffer));
        if(std::strcmp(buffer.company, name) == 0) {
            return new JobOffer{buffer};
        }
    }

    input.close();
    return nullptr;
}

int main() {
    int n;
    while(true) {
        std::cout << "1. Save job offers to file\n" << "2. Filter offer by salary\n" << "3. Find offer by company\n";
        std::cout << "Enter choice:";
        std::cin >> n;
        std::cin.ignore(1);
        switch(n) {
            case 1: {
                if (addJobOffers(FILE_PATH)) {
                    std::cout << "Saving was successful!" << std::endl;
                }
                else {
                    std::cout << "Saving failed!" << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "Enter salary:";
                size_t salary;
                std::cin >> salary;
                std::cin.ignore(1);
                filterOffer(FILE_PATH, salary);
                break;
            }
            case 3: {
                std::cout << "Enter company name:" << std::endl;
                char name[1024];
                std::cin.getline(name, 1024);
                JobOffer* offer = findOffer(FILE_PATH, name);
                if(offer != nullptr) {
                    std::cout << "Found the job offer!:" << std::endl;
                    printJobOffer(*offer);
                }
                else {
                    std::cout << "Offer was not found!" << std::endl;
                }

                delete offer;
                break;
            }
            default: {
                return 0;
            }
        }
    }
}