#pragma once
#include "IRenderable.h"
#include "Model.h"

class Skybox : public IRenderable, public Transformable
{
public:
	Skybox();
	~Skybox();

	void render(Shader* shader) override;

private:
	Model* skybox_;
	GLuint textureId_;
};

