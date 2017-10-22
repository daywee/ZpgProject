#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

class Light
{
public:
	Light();
	~Light();

	void setPosition(glm::vec3 position);
	void draw(Shader* shader);

private:
	glm::vec3 position_;

};

