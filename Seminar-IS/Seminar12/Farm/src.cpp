#include "Farm.h"
#include <utility>
int main()
{
	Farm f;
	f.addAnimal(AnimalType::Cat);
	f.addAnimal(AnimalType::Cat);
	f.addAnimal(AnimalType::Cat);
	f.addAnimal(AnimalType::Cat);

	f.addAnimal(AnimalType::Dog);
	f.addAnimal(AnimalType::Dog);

	f.addAnimal(AnimalType::Cow);
	f.addAnimal(AnimalType::Cow);

	f.addAnimal(AnimalType::Cow);
	f.addAnimal(AnimalType::Cow);
	f.addAnimal(AnimalType::Cow);
	f.addAnimal(AnimalType::Cow);

	f.makeSound();

	Farm f2(f);
	f2.makeSound();

	Farm f3;
	f3 = std::move(f);

	f3.makeSound();
}