#pragma once
#include "IRenderable.h"
#include <GL/glew.h>

class PlainObject : public IRenderable
{
public:
	PlainObject();
	~PlainObject();

	void render(Shader* shader) override;

private:
	GLuint vao_;
	GLuint vbo_;
	GLuint ibo_;
};

