#include <iostream>
#include "ShapesCollection.h"

int main()
{
	ShapesCollection c;

	c.addCircle(1, 1, 1);
	c.addCircle(1, 1, 2);

	c.addRectangle(1, 2, 3, 4);

	c.addTriangle(1, 2, 3, 4, 5, 6);
	c.addTriangle(1, 2, 3, 4, 5, 16);
	c.addTriangle(1, 2, 3, 4, 5, 26);
	c.addTriangle(1, 2, 3, 4, 5, 36);
	c.addTriangle(1, 2, 3, 4, 5, 56);
	c.addTriangle(1, 2, 3, 4, 5, 66);
	c.addTriangle(1, 2, 3, 4, 5, 76);

	c.printAreas();
}
