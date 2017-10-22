#include "Object.h"
#include <algorithm>

int Object::nextId = 0;

Object::Object()
{
	id_ = nextId++;
	transformation_ = new Transformation();

	// vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);
	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0); // enable vertex attributes

	// normal vector
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1); // enable vertex attributes

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
	glDrawArrays(GL_TRIANGLES, 0, 2880); // mode,first,count
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
