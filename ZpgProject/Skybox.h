#pragma once
#include "IRenderable.h"
#include "Model.h"

class Skybox : public IRenderable, public Transformable
{
public:
	Skybox();
	~Skybox();

	void render(Shader* shader) override;
	
	// we are only able to use transformation matrix of skybox
	// in render so we need to redirect it
	Transformation* transformation() const override
	{
		return skybox_->transformation();
	}

private:
	Model* skybox_;
	GLuint textureId_;
};

