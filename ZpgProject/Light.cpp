#include "Light.h"

Light::Light()
	: position_(glm::vec3())
{
}


Light::~Light()
{
}

void Light::setPosition(glm::vec3 position)
{
	position_ = position;
}

void Light::draw(Shader* shader)
{
	shader->useProgram();
	shader->useLightPosition(position_); // todo: observer
	shader->unuseProgram();
}
