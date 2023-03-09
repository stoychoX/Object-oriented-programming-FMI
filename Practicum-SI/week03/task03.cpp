#include <iostream>
#include <fstream>

struct JobOffer {
    char company[26];
    int employees;
    short yearlyPaidLeave;
    double projectCost;
};

void readJobOffer(JobOffer &offer) {
    offer = JobOffer{};
    std::cin.getline(offer.company, 26);
    std::cin >> offer.employees >> offer.yearlyPaidLeave >> offer.projectCost;
}

bool addJobOffers(const char* filePath) {
    size_t n;
    std::cin >> n;
    std::cin.ignore(1);
    JobOffer* offers = new JobOffer[n];
    std::cout << "Reading elements:" << std::endl;
    for(size_t i = 0; i < n; i++) {
        readJobOffer(offers[i]);
    }

    size_t count = 0;

    std::ifstream input(filePath, std::ios::in | std::ios::binary);
    if(input.is_open()) {
        input >> count;
        input.close();
    }

    std::ofstream output(filePath, std::ios::out | std::ios::binary);
    if(!input.is_open()) {
        return false;
    }
    count += n;
    output.write((const char*)&(count), sizeof((count)));
    output.seekp(0, std::ios::end);
    for(int i = 0; i < n; i++) {
        output.write((const char *)&offers[i], sizeof(offers[i]));
    }

    output.close();
    return false;
}

//- извежда на стандартния изход всички обяви със заплата по - висока от minSalary]
void filterOffer(const char* filePath, size_t minSalary) {
    
}

//  - проверява дали съществува оферта от фирма
void findOffer(const char* filePath, const char* name) {

}

int main() {
    addJobOffers("file.dat");
    return 0;
}