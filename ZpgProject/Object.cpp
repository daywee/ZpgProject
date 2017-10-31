#include "Object.h"
#include <algorithm>
#include "SuziFlat.h"
#include "SuziSmooth.h"

int Object::nextId = 0;

Object::Object()
{
	id_ = nextId++;
	transformation_ = new Transformation();

	// vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW); // sphere
	//glBufferData(GL_ARRAY_BUFFER, sizeof(suziFlat), suziFlat, GL_STATIC_DRAW); // suzi flat
	//glBufferData(GL_ARRAY_BUFFER, sizeof(suziSmooth), suziSmooth, GL_STATIC_DRAW); // suzi smooth
	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));

	// normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Object::~Object()
{
}

void Object::draw(Shader* shader)
{
	shader->useProgram();
	shader->useMatrix(transformation()->matrix());

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 2880); // sphere
	//glDrawArrays(GL_TRIANGLES, 0, 2904); // suzi flat
	//glDrawArrays(GL_TRIANGLES, 0, 2904); // suzi smooth
	glBindVertexArray(0);

	shader->unuseProgram();
}

Transformation* Object::transformation()
{
	return transformation_;
}

int Object::getId()
{
	return id_;
}
