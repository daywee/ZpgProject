#include "Camera.h"



Camera::Camera()
	: eye_(glm::vec3(0, 0, 10)), target_(glm::vec3(0)), up_(glm::vec3(0, 1.0f, 0)), fov_(45.0f), aspect_(4.0f / 3.0f), near_(0.1f), far_(100.0f)
{
}


Camera::~Camera()
{
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(fov_, aspect_, near_, far_);
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(eye_, target_, up_);
}

void Camera::setTarget(float fi, float psi)
{
}

void Camera::setPosition(float x, float y, float z)
{
}

void Camera::toLeft()
{
}

void Camera::toRight()
{
}
