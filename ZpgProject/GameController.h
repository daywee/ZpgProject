#pragma once
#include "Camera.h"

class GameController
{
public:
	~GameController();
	static GameController* getInstance();

	void pressKey(int key);
	void releaseKey(int key);
	void moveMouse(double mouseX, double mouseY);

	void setCamera(Camera* camera);
	void update() const;

private:
	GameController();

	static GameController* instance;

	bool forward_;
	bool backward_;
	bool left_;
	bool right_;
	bool up_;
	bool down_;

	double prevMouseX_;
	double prevMouseY_;

	Camera* camera_;
};

