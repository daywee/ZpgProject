#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;
	void setTarget(float fi, float psi);
	void setTarget(glm::vec3 target);
	void setTarget(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);
	void toLeft();
	void toRight();

private:
	glm::vec3 eye_;
	glm::vec3 target_;
	glm::vec3 up_;

	glm::mat4 projection_;

	float fov_;
	float aspect_;
	float near_;
	float far_;

};

