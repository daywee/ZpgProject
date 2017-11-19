#pragma once
class Shader;

class IRenderable
{
public:

	IRenderable()
	{
	}

	virtual ~IRenderable()
	{
	}

	virtual void render(Shader* shader) = 0;
};

