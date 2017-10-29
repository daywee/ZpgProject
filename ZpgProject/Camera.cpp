#include "Camera.h"

Camera::Camera()
	: eye_(glm::vec3(0, 0, 10)), up_(glm::vec3(0, 1.0f, 0)), fov_(45.0f), aspect_(4.0f / 3.0f), near_(0.1f), far_(100.0f)
{
	// todo: why are these default values?
	fi_ = glm::radians(270.f);
	psi_ = glm::radians(90.f);
	setTarget(fi_, psi_);
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
	fi_ = fi;
	psi_ = psi;
	target_ = eye_ + glm::vec3(glm::cos(fi_) * glm::sin(psi_), glm::cos(psi_), glm::sin(fi_) * glm::sin(psi_));
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

void Camera::moveRight()
{
	const auto vec = glm::cross(glm::normalize(up_), glm::normalize(target_ - eye_));
	eye_ -= vec;
	target_ -= vec;
	notifyObservers();
}

void Camera::moveLeft()
{
	const auto vec = glm::cross(glm::normalize(up_), glm::normalize(target_ - eye_));
	eye_ += vec;
	target_ += vec;
	notifyObservers();
}

void Camera::moveForward()
{
	const auto vec = glm::normalize(target_ - eye_);
	eye_ += vec;
	target_ += vec;
	notifyObservers();
}

void Camera::moveBackward()
{
	const auto vec = glm::normalize(target_ - eye_);
	eye_ -= vec;
	target_ -= vec;
	notifyObservers();
}

void Camera::rotateRight()
{
	setTarget(fi_ + 0.1f, psi_);
	notifyObservers();
}

void Camera::rotateLeft()
{
	setTarget(fi_ - 0.1f, psi_);
	notifyObservers();
}

void Camera::rotateUp()
{
	setTarget(fi_, psi_ - 0.1f);
	notifyObservers();
}

void Camera::rotateDown()
{
	setTarget(fi_, psi_ + 0.1f);
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
