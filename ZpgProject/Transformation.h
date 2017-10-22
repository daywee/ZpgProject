#pragma once
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation
{
public:
	Transformation();
	~Transformation();

	glm::mat4 matrix() const;

	void setPosition(glm::vec3 position);
	void setSize(glm::vec3 size);
	void setAngleRadians(float angle);
	void setAngleDegrees(float angle);

private:

	glm::vec3 position_;
	glm::vec3 size_;
	float angle_;
	glm::vec3 angleAxis_;
};
