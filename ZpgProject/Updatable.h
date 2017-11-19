#pragma once
#include <functional>
#include "IUpdatable.h"

class Updatable : public IUpdatable
{
public:
	using Func = std::function<void()>;

	Updatable()
		:onUpdate_([](){})
	{
	}

	virtual ~Updatable()
	{
	}

	void onUpdate(Func func)
	{
		onUpdate_ = func;
	}

	void update() override
	{
		onUpdate_();
	}

private:
	Func onUpdate_;

};

