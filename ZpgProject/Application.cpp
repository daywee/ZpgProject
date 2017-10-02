#include "Application.h"
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "Scene.h"


Application::Application()
{
	initWindow();
	shader_ = new Shader();
	scene_ = new Scene();
}

Application::~Application()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::run()
{
	while (!glfwWindowShouldClose(window_))
	{
		scene_->render(window_, shader_->getShaderProgram());
	}
}

void Application::initWindow()
{
	glfwSetErrorCallback(this->errorCallback);

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window_ = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);

	if (!window_)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window_);
	glfwSwapInterval(1);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	int width, height;
	glfwGetFramebufferSize(window_, &width, &height);
	//float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::errorCallback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::printVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
