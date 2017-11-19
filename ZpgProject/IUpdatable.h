#pragma once

class IUpdatable
{
public:
	IUpdatable()
	{
	}

	virtual ~IUpdatable()
	{
	}

	virtual void update() = 0;
};

