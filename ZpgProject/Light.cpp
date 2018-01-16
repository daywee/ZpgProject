#include "Light.h"

Light::Light()
	: position_(glm::vec3())
{
}

Light::Light(glm::vec3 position)
	: position_(position)
{
}


Light::~Light()
{
}

void Light::setPosition(glm::vec3 position) // todo: use Transformable
{
	position_ = position;
}

glm::vec3 Light::getPosition()
{
	return position_;
}

void Light::render(Shader* shader)
{
	shader->useProgram();
	shader->useLightPosition(position_); // todo: observer
	shader->unuseProgram();
}
