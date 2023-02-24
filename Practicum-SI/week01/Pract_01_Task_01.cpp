#include <iostream>

size_t isLessByValue(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

size_t isLessByReference(const size_t& a, const size_t& b)
{
	return (a < b) ? a : b;
}

size_t isLessByPointer(size_t* a, size_t* b)
{
	return ((*a) < (*b)) ? (*a) : (*b);
}
int main()
{
	std::cout << isLessByValue(5, 6) << std::endl;
	std::cout << isLessByReference(5, 6) << std::endl;
	size_t a = 10;
	size_t b = 11;
	std::cout << isLessByPointer(&a, &b);

	return 0;
}

//Реализирайте три функции, 
//която по две цели числа връщат 
//по - малкото от тях.Функциите да
//подават числата съответно по стойност,
//като указател и чрез референция(псевдоним).
//Използвайте ключова дума const и 
//демонстрирайте чрез примери как и
//кога е възможна(и кога не) употребата на всяка една от функциите.