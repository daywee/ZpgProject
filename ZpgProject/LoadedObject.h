#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "Transformable.h"
#include "Updatable.h"
#include "IRenderable.h"

// todo: merge into object, this is only temporary!!!
class LoadedObject : public Transformable, public Updatable, public IRenderable
{
public:
	LoadedObject(int vertexCount, GLuint vao, GLuint vbo, GLuint ibo);
	~LoadedObject();

	void render(Shader* shader) override;

private:
	GLuint vao_;
	GLuint vbo_;
	GLuint ibo_;
	int indicesCount_;
};

