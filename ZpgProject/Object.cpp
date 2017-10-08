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
}

Object::~Object()
{
}

void Object::bindVertexArray()
{
	glBindVertexArray(vao_);
}

void Object::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3); // mode,first,count
}

void Object::setPosition(glm::vec3 position)
{
	transformation_->setPosition(position);
}

void Object::setSize(glm::vec3 size)
{
	transformation_->setSize(size);
}

void Object::setAngle(float angle)
{
	transformation_->setAngle(angle);
}

glm::mat4 Object::getTransformationMatrix()
{
	return transformation_->getTransformation();
	//return *transformationMatrix_;
	// TODO: remove
}

int Object::getId()
{
	return id_;
}
