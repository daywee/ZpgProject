#include "Transformation.h"

Transformation::Transformation()
	: position_(glm::vec3(0.0f, 0.0f, 0.0f)), size_(glm::vec3(1.0f, 1.0f, 1.0f)), angle_(0), angleAxis_(glm::vec3(0.0f, 0.0f, 1.0f))
{
}

Transformation::~Transformation()
{
}

glm::mat4 Transformation::getTransformation() const
{
	glm::mat4 matrix = glm::mat4();

	matrix = glm::rotate(matrix, angle_, angleAxis_);
	matrix = glm::scale(matrix, size_);
	matrix = glm::translate(matrix, position_);

	return matrix;
}

void Transformation::setPosition(const glm::vec3 position)
{
	this->position_ = position;
}

void Transformation::setSize(const glm::vec3 size)
{
	this->size_ = size;
}

void Transformation::setAngle(const float angle)
{
	this->angle_ = angle;
}
