#pragma once
#include "DynamicCollection.h"
class NormalCollection : public DynamicCollection
{
public:
	virtual void add(int) override;
	virtual void remove(int) override;
	virtual size_t count(int) const override;
	virtual bool contains(int) const override;

	~NormalCollection() override = default;
};

