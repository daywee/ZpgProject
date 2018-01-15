#include "Application.h"
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "Scene.h"
#include "SceneFactory.h"
#include "GameController.h"

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
	camera_ = new Camera();
	scene_ = SceneFactory::houseSceneNew(camera_);
	gameController_ = GameController::getInstance();
	gameController_->setCamera(camera_);
	printVersionInfo();
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
		const auto start = std::chrono::system_clock::now();

		double mouseX, mouseY;
		glfwGetCursorPos(window_, &mouseX, &mouseY);
		gameController_->moveMouse(mouseX, mouseY);
		scene_->update();
		gameController_->update();
		scene_->render(window_);
		glfwPollEvents();

		printFps(start, std::chrono::system_clock::now());
	}
}

void Application::initCallbacks()
{
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	if (action == GLFW_PRESS)
		gameController_->pressKey(key);
	if (action == GLFW_RELEASE)
		gameController_->releaseKey(key);
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

void Application::printFps(const Time start, const Time end) const
{
	// todo: print it less often

	const chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
	const double fps = 1. / (elapsed.count() / 1000.);
	std::string title = "ZPG - FPS: " + std::to_string(static_cast<int>(fps));
	
	glfwSetWindowTitle(window_, title.c_str());
}
