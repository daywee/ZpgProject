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
	notifyObservers();
}

void Camera::setTarget(glm::vec3 target)
{
	target_ = target;
	notifyObservers();
}

void Camera::setTarget(float x, float y, float z)
{
	target_ = glm::vec3(x, y, z);
	notifyObservers();
}

void Camera::setPosition(float x, float y, float z)
{
	eye_ = glm::vec3(x, y, z);
	notifyObservers();
}

void Camera::setPosition(glm::vec3 position)
{
	eye_ = position;
	notifyObservers();
}

void Camera::toLeft() // todo: test funcionality
{
	eye_ += glm::normalize(glm::cross(target_, up_));
	notifyObservers();
}

void Camera::toRight() // todo: test functionality
{
	eye_ -= glm::normalize(glm::cross(target_, up_));
	notifyObservers();
}

void Camera::addObserver(IObserver* observer)
{
	observers_.push_back(observer);
}

void Camera::removeObserver(IObserver* observer)
{
	for (std::vector<IObserver*>::iterator iterator = observers_.begin(); iterator != observers_.end(); ++iterator)
	{
		if (*iterator == observer)
		{
			observers_.erase(iterator);
			break;
		}
	}
}

void Camera::notifyObservers()
{
	for each (auto observer in observers_)
	{
		observer->notify(this);
	}
}
