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
	void setPosition(float x, float y, float z);
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

