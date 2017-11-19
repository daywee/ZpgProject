#include "LoadedObject.h"


LoadedObject::LoadedObject(const int indicesCount, const GLuint vao, const GLuint vbo, const GLuint ibo)
{
	indicesCount_ = indicesCount;
	vao_ = vao;
	vbo_ = vbo;
	ibo_ = ibo;
}

LoadedObject::~LoadedObject()
{
}

void LoadedObject::render(Shader* shader)
{
	shader->useProgram();
	shader->useMatrix(transformation()->matrix());

	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, indicesCount_, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

	shader->unuseProgram();
}
