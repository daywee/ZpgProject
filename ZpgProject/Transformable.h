#pragma once
#include "Transformation.h"

class Transformable
{
public:
	Transformable()
		: transformation_(new Transformation())
	{
	}

	virtual ~Transformable()
	{
	}

	virtual Transformation* transformation() const
	{
		return transformation_;
	}

private:
	Transformation* transformation_;
};

