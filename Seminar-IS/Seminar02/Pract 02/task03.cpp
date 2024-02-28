#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

#pragma warning(disable : 4996)

enum class Tyres {
    Soft=45,
    Medium=50,
    Hard=60,
    Intern=40,
    Wet=35
};

const size_t MAX_NAME_LENGTH = 65;
const size_t MAX_TYRE_LENGTH = 10;
const size_t MAX_ROW_SIZE = 70;

struct Bolid {
    double tyreWearCoefficient;
    size_t maxLoops;
    Tyres tyres;
    short int yearOfManafacture;
    char name[MAX_NAME_LENGTH];
    bool inRepairStation;
};

void readTyres(Tyres& tyres) {
    char* type = new char[MAX_TYRE_LENGTH];
    cin.getline(type, MAX_TYRE_LENGTH);
    if (strcmp(type, "Soft") == 0) {
        tyres = Tyres::Soft;
    }
    else if (strcmp(type, "Medium") == 0) {
        tyres = Tyres::Medium;
    }
    else if (strcmp(type, "Hard") == 0) {
        tyres = Tyres::Hard;
    }
    else if (strcmp(type, "Intern") == 0) {
        tyres = Tyres::Intern;
    }
    else if (strcmp(type, "Wet") == 0) {
        tyres = Tyres::Wet;
    }
    delete[] type;
}

void readBolid(Bolid& bolid) {
    cout << "Name: ";
    cin.getline(bolid.name, MAX_NAME_LENGTH);
    cout << "Year of manafacture: ";
    cin >> bolid.yearOfManafacture;
    cin.ignore();
    cout << "Tyres: ";
    readTyres(bolid.tyres);
    cout << "Tyre wear coefficient: ";
    cin >> bolid.tyreWearCoefficient;
    cout << "Is in repair station?: ";
    bolid.inRepairStation = cin.get()=='1';
    cin.ignore();
    cout << "Max loops: ";
    cin >> bolid.maxLoops;
    cin.ignore();
}

size_t calcMaxLoops(const Bolid& bolid) {
    return bolid.maxLoops * bolid.tyreWearCoefficient;
}

void sortBolids(Bolid* bolids, const size_t size) {
    size_t* indexes = new size_t[size];
    for (size_t i = 0; i < size; i++) {
        indexes[i] = i;
    }
    for (size_t i = 0; i < size; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < size; j++) {
            if (bolids[min_index].yearOfManafacture > bolids[j].yearOfManafacture) {
                min_index = j;
            }
        }
        Bolid temp = bolids[i];
        bolids[i] = bolids[min_index];
        bolids[min_index] = temp;
    }
    delete[] indexes;
}

void saveToCSV(Bolid* bolids, size_t size){
    ofstream outFile("result.csv");
    if(!outFile.is_open()){
        return;    
    }
    sortBolids(bolids, size);
    for(size_t i=0;i<size;i++){
        outFile << bolids[i].name << "," << bolids[i].yearOfManafacture  << "," << (int)bolids[i].tyres << "," << bolids[i].tyreWearCoefficient << "," << bolids[i].inRepairStation << "," << bolids[i].maxLoops << '\n';
    }
    outFile.close();
}

void readFromCSV(){
    ifstream inFile("result.csv");
    if(!inFile.is_open()){
        return;    
    }

    char* row = new char[MAX_ROW_SIZE];
    inFile.getline(row, MAX_ROW_SIZE);
    while(!inFile.eof()){
        for(size_t i=0;i<strlen(row);i++){
            if(row[i] == ','){
                row[i] = '\n';            
            }        
        }
        cout << row;
        inFile.getline(row, MAX_ROW_SIZE);
    }
    delete[] row;
    inFile.close();
}

int main()
{
    //Bolid bolid;
    /*readBolid(bolid);

    cout << bolid.name << endl;
    cout << bolid.yearOfManafacture << endl;
    cout << (int)bolid.tyres << endl;
    cout << bolid.tyreWearCoefficient << endl;
    cout << bolid.inRepairStation << endl;
    cout << bolid.maxLoops << endl;*/

    /*size_t size;
    cout << "Amount of bolids: ";
    cin >> size;
    cin.ignore();

    Bolid* bolids = new Bolid[size];
    for (int i = 0; i < size; i++) {
        cout << "Bolid " << i+1 << endl;
        readBolid(bolids[i]);
    }*/
    
    /*size_t size = 1;
    Bolid* bolids = new Bolid[size];
    bolids[0] = {1,2,Tyres::Wet,4,"susu",false};
    saveToCSV(bolids, size);
    delete[] bolids;
    */

    
    readFromCSV();
}
