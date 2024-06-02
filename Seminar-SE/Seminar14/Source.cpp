#include <iostream>
#include "polymorphic_container.hpp"

struct Base
{
	virtual void f() const = 0;

	virtual Base* clone() const = 0;

	virtual ~Base() = default;
};

struct DerOne : Base
{

	void f() const override
	{
		std::cout << "DerOne::Base" << std::endl;
	}

	// Inherited via Base
	Base* clone() const override
	{
		return new DerOne(*this);
	}
};


struct DerTwo : Base
{
	void f() const override
	{
		std::cout << "DerTwo::Base" << std::endl;
	}

	// Inherited via Base
	Base* clone() const override
	{
		return new DerTwo(*this);
	}
};

void f_on_cantainer(const polymorphic_container<Base>& c)
{
	c.execute(0, [](const Base* b) -> void { b->f(); });
	c.execute(2, [](const Base* b) -> void { b->f(); });
}

int main()
{
	polymorphic_container<Base> c;

	c.add(new DerOne);
	c.add(new DerOne);
	c.add(new DerTwo);

	f_on_cantainer(c);
}