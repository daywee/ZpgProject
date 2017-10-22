#pragma once
#include "ISubject.h"

class ISubject;

class IObserver
{
public:
	IObserver()
	{
	}

	virtual ~IObserver()
	{
	}

	virtual void notify(ISubject* subject) = 0;
};
