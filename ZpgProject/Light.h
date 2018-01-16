#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "IRenderable.h"

class Light : public IRenderable
{
public:
	Light();
	Light(glm::vec3 position);
	~Light();

	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void render(Shader* shader) override;

private:
	glm::vec3 position_;

};

