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
	glBufferData(GL_ARRAY_BUFFER, sizeof(points_), points_, GL_STATIC_DRAW);
	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glEnableVertexAttribArray(0); // enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

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
	shader->useMatrix(transformationMatrix());

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 3); // mode,first,count
	glBindVertexArray(0);

	shader->unuseProgram();
}

Transformation* Object::transformation()
{
	return transformation_;
}

glm::mat4 Object::transformationMatrix()
{
	return transformation_->getTransformation();
}

int Object::getId()
{
	return id_;
}
