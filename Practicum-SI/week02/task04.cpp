#include<iostream>
#include<fstream>
#include<cstring>

#define LOG_NAME_LEN 16
#pragma warning (disable : 4996)

union ipAddress {
    int data;
    unsigned char p[4];
};

struct dateTime {
    int sec;
    int min;
    int hrs;
};

struct log {
    char name[LOG_NAME_LEN];
    ipAddress ipv4;
    dateTime logTime;
};

void writeIP(const ipAddress& arg, std::ofstream& outFile) {
    for (int i = 3; i >= 0; i--)
        outFile << (int)(arg.p[i]) << ".";
    outFile << " ";    
}

void writeDateTime(const dateTime& dt, std::ofstream& outFile) {
    outFile << dt.hrs << ":" << dt.min << ":" << dt.sec;
}

void writeLog(const log& toWrite, std::ofstream& outFile) {
    // Първо записваме името
    outFile << toWrite.name << " ";
    
    // След това записваме ip адреса
    writeIP(toWrite.ipv4, outFile);

    // и датата
    writeDateTime(toWrite.logTime, outFile);

    outFile << std::endl;

    // Сега моделът е <name> <ip> <hrs>:<mins>:<sec>
}

bool writeLogs(log* logs, size_t size, const char* filePath) {
    // Сега това става лесно:
    std::ofstream outFile(filePath);

    if(!outFile.is_open())
        return false;

    for (size_t i = 0; i < size; i++)
        writeLog(logs[i], outFile);
    
    outFile.close();
    return true;
}

void readDateTime(dateTime& dt, std::ifstream& inFile) {
    inFile >> dt.hrs;
    inFile.get();               // Пропусни ":"
    inFile >> dt.min;
    inFile.get();               // Пропусни ":"
    inFile >> dt.sec;
}

void readIP(ipAddress& ip, std::ifstream& inFile) {
    int x = 0;

    for (int i = 3; i >= 0; i--) {
        // Когато записвахме ip адреса го записвахме като интове. Сега просто си го прочитаме обратно.
        inFile >> x;                                    
        ip.p[i] = (unsigned char)(x);                         
        inFile.get();                                   // Пропусни "."
    }

    inFile.get();                                      // Пропускаме " "
}

void readLog(log& toRead, std::ifstream& inFile) {
    // Следваме модела по който записахме лога
    inFile >> toRead.name;
    char c = inFile.get();
    readIP(toRead.ipv4, inFile);
    readDateTime(toRead.logTime, inFile);

    inFile.get(); // Пропусни std::endl    
}

// Връща колко лога има в един файл. Всеки лог записва точно един път std::endl (символа за нов ред \n).
// Има и по - лесен начин, но за него следващия път!
size_t logCount(const char* filePath) {
    size_t cnt = 0;

    std::ifstream inFile(filePath);

    if(!inFile.is_open())
        return 0;
    
    char buff;

    while(true) {
        buff = inFile.get();

        if(inFile.eof())
            break;
        
        if(buff == '\n')
            ++cnt;
    }
    return cnt;
}

// Тук заделяме памет!!! Ще е добре да си я изтрием!
log* readLogs(size_t& size, const char* filePath) {
    size = logCount(filePath);

    if(size == 0)
        return nullptr;

    log* logs = new log[size];

    // Отваряме поток 2 пъти един за да видим колко
    // лога имаме и втори за да ги прочетем.
    // Отново: това може да стане само с едно отваряне,
    // но ще се разглежда следващия път.
    std::ifstream inFile(filePath);

    for (size_t i = 0; i < size; i++)
        readLog(logs[i], inFile);
    
    return logs;
}

bool initLog(log& toInit, const char* name, int ip, uint8_t hrs, uint8_t mins, uint8_t sec) {
    if(strlen(name) > 16)
        return false;              

    if(hrs > 23 || mins > 59 || sec > 59)
        return false;

    strcpy(toInit.name, name);

    toInit.ipv4.data = ip;
    
    toInit.logTime = {sec, mins, hrs};    
    return true;
}

void printLog(const log& lg) {
    std::cout << lg.name << " ";

    for (int i = 3; i >= 1; i--)
        std::cout << (unsigned)(lg.ipv4.p[i]) << ".";
    
    std::cout << (unsigned)(lg.ipv4.p[0]);

    std::cout << " " << lg.logTime.hrs << ":" << lg.logTime.min << ":" << lg.logTime.sec << std::endl;    
}

void printLogs(log* logs, size_t size) {
    for (size_t i = 0; i < size; i++)
        printLog(logs[i]);
}

int main() {
    // Бързо примерче
    log myLogs[5];

    // Тези големи числа всъщност кодират ip адреси
    // https://www.browserling.com/tools/ip-to-dec

    initLog(myLogs[0], "Yavor", 2130706433, 12, 14, 0);
    initLog(myLogs[1], "Hristo", 3221290750, 14, 0, 2);
    initLog(myLogs[2], "Nikola", 4294967295, 17, 0, 4);
    initLog(myLogs[3], "Ivan", 3221291364, 1, 1, 0);
    initLog(myLogs[4], "Alex", 3194224640, 2, 59, 59);

    std::cout << "Sample logs: " << std::endl;
    printLogs(myLogs, 5);
    std::cout << std::endl;

    std::cout << "Writing logs..." << std::endl << std::endl;
    writeLogs(myLogs, 5, "logs-database.txt");
    
    std::cout << "Logs written" << std::endl << "Creating a copy of the logs from the file..." << std::endl << std::endl;
    
    size_t size = 0;
    log* copy = readLogs(size, "logs-database.txt");
    std::cout << "Created copy from the file: " << std::endl << std::endl;
    printLogs(copy, size);

    delete[] copy;
}
