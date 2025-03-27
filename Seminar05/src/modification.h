#pragma once
#include <fstream>

enum ModificationType
{
	Up, 
	Down
};

namespace ModificationConstants
{
	const double INVALID_PERCENT = -1.0;
	const unsigned INVALID_AMOUNT = (unsigned)(-1);
}

// Modify a price.
// Amount could easily be double too.
struct Modification
{
	char* name = nullptr;
	double percent = ModificationConstants::INVALID_PERCENT;
	unsigned amount = ModificationConstants::INVALID_AMOUNT;
	ModificationType type;
};

Modification createPercentModif(const char* name, double percent, ModificationType type);
Modification createAmountModif(const char* name, unsigned amount, ModificationType type);

bool isAmountModif(const Modification& modif);
bool isPercentModif(const Modification& modif);

void writeModif(std::ofstream& outFile, const Modification& modif);
void readModif(std::ifstream& inFile, Modification& modif);

void readModifications(const char* fileName, Modification*& modifs, unsigned& size);
void writeModifications(const char* fileName, const Modification* modifs, unsigned size);