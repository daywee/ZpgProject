#include "GameController.h"
#include <GLFW/glfw3.h>


GameController* GameController::instance = nullptr;

GameController::GameController()
{
}


GameController::~GameController()
{
}

GameController* GameController::getInstance()
{
	if (instance == nullptr)
		instance = new GameController();

	return instance;
}

void GameController::pressKey(const int key)
{
	if (key == GLFW_KEY_W)
		forward_ = true;
	if (key == GLFW_KEY_S)
		backward_ = true;
	if (key == GLFW_KEY_A)
		left_ = true;
	if (key == GLFW_KEY_D)
		right_ = true;
	if (key == GLFW_KEY_SPACE)
		up_ = true;
	if (key == GLFW_KEY_X)
		down_ = true;
}

void GameController::releaseKey(const int key)
{
	if (key == GLFW_KEY_W)
		forward_ = false;
	if (key == GLFW_KEY_S)
		backward_ = false;
	if (key == GLFW_KEY_A)
		left_ = false;
	if (key == GLFW_KEY_D)
		right_ = false;
	if (key == GLFW_KEY_SPACE)
		up_ = false;
	if (key == GLFW_KEY_X)
		down_ = false;
}

void GameController::moveMouse(const double mouseX, const double mouseY)
{
	const float xDiff = (mouseX - prevMouseX_) / 1000;
	camera_->rotateX(xDiff);

	const float yDiff = (prevMouseY_ - mouseY) / 1000;
	camera_->rotateY(yDiff);

	prevMouseX_ = mouseX;
	prevMouseY_ = mouseY;
}

void GameController::setCamera(Camera* camera)
{
	camera_ = camera;
}

void GameController::update() const
{
	if (camera_ != nullptr)
	{
		if (forward_)
			camera_->moveForward();
		if (backward_)
			camera_->moveBackward();
		if (left_)
			camera_->moveLeft();
		if (right_)
			camera_->moveRight();
		if (up_)
			camera_->moveUp();
		if (down_)
			camera_->moveDown();
	}
}
