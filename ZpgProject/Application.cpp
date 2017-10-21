#include "Application.h"
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "Scene.h"

Application* Application::instance = nullptr;

Application* Application::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Application();
	}
	return instance;
}

Application::Application()
{
	initWindow();
	initCallbacks();
	shader_ = new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	scene_ = new Scene();
	camera_ = new Camera();
}

Application::~Application()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::run()
{
	Object* object1 = new Object();
	//Object* object2 = new Object();
	scene_->addObject(object1);
	//scene_->addObject(object2);


	float a = 0.01f;
	while (!glfwWindowShouldClose(window_))
	{
		object1->setPosition(glm::vec3(0.f, 0.0f, 0.0f));
		object1->setAngle(glfwGetTime());
		scene_->render(window_, shader_, camera_);
		a += 0.01f;
		//object2->rotate(-0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		//object_->scale(glm::vec3(1.01f, 1.0f, 1.0f));
		//object_->translate(glm::vec3(0.0f, 0.001f, 0.0f));
	}
}

void Application::initCallbacks()
{
	glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double mouseX, double mouseY) -> void { getInstance()->cursorPosCallback(window, mouseX, mouseY); });
	glfwSetErrorCallback([](int error, const char* description) -> void { getInstance()->errorCallback(error, description); });
	glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void { getInstance()->keyCallback(window, key, scancode, action, mods); });
	glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) -> void { getInstance()->mouseButtonCallback(window, button, action, mods); });
	glfwSetWindowFocusCallback(window_, [](GLFWwindow* window, int focused) -> void { getInstance()->windowFocusCallback(window, focused); });
	glfwSetWindowIconifyCallback(window_, [](GLFWwindow* window, int iconified) -> void { getInstance()->windowIconifyCallback(window, iconified); });
	glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) -> void { getInstance()->windowSizeCallback(window, width, height); });
}

void Application::initWindow()
{
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
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::cursorPosCallback(GLFWwindow* window, double mouseX, double mouseY)
{
	printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);
}

void Application::errorCallback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scanCode, action, mods);
}

void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	printf("mouse_button_callback %d, %d, %d \n", button, action, mods);
}

void Application::windowFocusCallback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback %d \n", focused);
}

void Application::windowIconifyCallback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback %d \n", iconified);
}

void Application::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::printVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
