#include "prize.h"
#include "modification.h"
#include <iostream>

double applyModif(double oldPrice, const Modification& modif)
{
	int type = (modif.type == ModificationType::Up) ? 1 : -1;

	if (isAmountModif(modif))
	{
		// this is the fixed amount case
		oldPrice += type * (modif.amount);
	}
	else if(isPercentModif(modif))
	{
		oldPrice += type * ((oldPrice * modif.percent) / 100);
	}

	return oldPrice;
}

double getNewPrice(double oldPrice, const Modification* modifs, unsigned modifSize)
{
	for (size_t i = 0; i < modifSize; i++)
	{
		oldPrice = applyModif(oldPrice, modifs[i]);
	}

	return oldPrice;
}

void showPriceModifications(const char* priceFile, const char* modifFile)
{
	Price* prices = nullptr;
	unsigned priceSize = 0;

	Modification* modifs = nullptr;
	unsigned modifSize = 0;

	readPrizes(priceFile, prices, priceSize);
	readModifications(modifFile, modifs, modifSize);

	for (size_t i = 0; i < priceSize; i++)
	{
		double newPrice = getNewPrice(prices[i].amount, modifs, modifSize);
		printPrize(prices[i]);
		std::cout << newPrice << " " << prices[i].currency << std::endl << std::endl;
	}
}

const char* MODIF_FILE_NAME = "modifs.dat";
const char* PRICE_FILE_NAME = "prices.dat";

void createExample()
{
	// Create prices
	Price prices[4] =
	{
		createPrice(10, "USD"),
		createPrice(16, "USD"),
		createPrice(20, "BGN"),
		createPrice(24, "USD")
	};

	writePrices(PRICE_FILE_NAME, prices, 4);

	// Create modifications
	Modification modifs[2] =
	{
		createAmountModif("Add 5", 5, ModificationType::Up),
		createPercentModif("Down 5 percent", 5, ModificationType::Down)
	};

	writeModifications(MODIF_FILE_NAME, modifs, 2);
}

int main()
{
	createExample();

	showPriceModifications(PRICE_FILE_NAME, MODIF_FILE_NAME);
}