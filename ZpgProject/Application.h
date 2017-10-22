#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Camera.h"

class Application
{
public:
	~Application();
	static Application* getInstance();

	void run();

private:
	Application();

	static Application* instance;

	GLFWwindow* window_;
	Scene* scene_;
	Camera* camera_;

	void initCallbacks();
	void initWindow();
	void printVersionInfo();

	void cursorPosCallback(GLFWwindow* window, double mouseX, double mouseY);
	void errorCallback(int error, const char* description);
	void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void windowFocusCallback(GLFWwindow* window, int focused);
	void windowIconifyCallback(GLFWwindow* window, int iconified);
	void windowSizeCallback(GLFWwindow* window, int width, int height);
};
	