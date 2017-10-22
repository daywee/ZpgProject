#pragma once
#include "IObserver.h"

class IObserver;

class ISubject
{
public:
	ISubject()
	{
	}

	virtual ~ISubject()
	{
	}

	virtual void addObserver(IObserver* observer) = 0;
	virtual void removeObserver(IObserver* observer) = 0;
};
