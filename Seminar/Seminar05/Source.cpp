#include<iostream>
#include"Event.h"
#include"EventCollection.h"


/*
				 --GEOM--
-----DSTR--------

		   --DIS--
----OOP---
11   12   13   14   15   16   17   18
*/

void printEvent(const Event& e) {
	std::cout << e.getName() << std::endl;
}

int main() {
	EventCollection e;

	Event OOP("OOP", 
		24, 3, 2023,
		11, 0, 0,
		13, 0, 0
		);

	Event DSTR("DIS",
		24, 3, 2023,
		13, 0, 0,
		14, 0, 0
	);

	Event DIS("DSTR",
		24, 3, 2023,
		11, 0, 0,
		14, 0, 0
	);

	Event GEOM("GEOM",
		24, 3, 2023,
		14, 0, 0,
		16, 0, 0
	);

	Event ev("Name",
		25, 3, 2023,
		22, 0, 0,
		23, 0, 0
	);

	
	e.addEvent(OOP);
	e.addEvent(DIS);
	e.addEvent(DSTR);
	e.addEvent(GEOM);
	e.addEvent(ev);

	Date argDate(24, 3, 2023);

	EventCollection res = e.getMaxEvents(argDate);

	for (size_t i = 0; i < res.getSize(); i++)
		printEvent(res.getByIndex(i));
}