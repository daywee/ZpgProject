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
	target_ = glm::vec3(glm::cos(fi), glm::sin(fi), glm::sin(psi));
}

void Camera::setTarget(glm::vec3 target)
{
	target_ = target;
}

void Camera::setTarget(float x, float y, float z)
{
	target_ = glm::vec3(x, y, z);
}

void Camera::setPosition(float x, float y, float z)
{
	eye_ = glm::vec3(x, y, z);
}

void Camera::setPosition(glm::vec3 position)
{
	eye_ = position;
}

void Camera::toLeft() // todo toLeft()
{
	eye_ += glm::normalize(glm::cross(target_, up_));
}

void Camera::toRight() // todo toRight()
{
	eye_ -= glm::normalize(glm::cross(target_, up_));
}
