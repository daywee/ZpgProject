#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Camera.h"
#include "GameController.h"
#include <chrono>

class Application
{
public:
	~Application();
	static Application* getInstance();

	void run();

private:
	using Time = std::chrono::time_point<std::chrono::system_clock>;

	Application();

	static Application* instance;

	GLFWwindow* window_;
	Scene* scene_;
	Camera* camera_;
	GameController* gameController_;

	double fpsStack[100];
	int currentFps = 0;

	void initCallbacks();
	void initWindow();
	void printVersionInfo();
	void printFps(Time start, Time end);

	void errorCallback(int error, const char* description);
	void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void windowFocusCallback(GLFWwindow* window, int focused);
	void windowIconifyCallback(GLFWwindow* window, int iconified);
	void windowSizeCallback(GLFWwindow* window, int width, int height);
};
	