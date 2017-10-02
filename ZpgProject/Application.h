#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Scene.h"

class Application
{
public:
	Application();
	~Application();

	void run();

private:
	GLFWwindow* window_;
	Shader* shader_;
	Scene* scene_;

	void initWindow();
	static void errorCallback(int error, const char* description);
	void printVersionInfo();
};
