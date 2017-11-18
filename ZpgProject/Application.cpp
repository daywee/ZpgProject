#include "Application.h"
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "Scene.h"
#include "Light.h"
#include <chrono>

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
	scene_ = new Scene(new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl"));
	camera_ = new Camera();
	camera_->addObserver(scene_);
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
	Object* object1 = new Object(Sphere);
	Object* object2 = new Object(Plain);
	Object* object3 = new Object(SuziFlat);
	Object* object4 = new Object(SuziSmooth);
	Object* object5 = new Object(Plain);
	scene_->addObject(object1);
	object1->onUpdate = [object1]()
	{
		object1->transformation()->setPosition(glm::vec3(glm::sin(glfwGetTime()) * 5, 0, 0));
	};
	scene_->addObject(object2);
	scene_->addObject(object3);
	float angle = 0.0f;
	object3->onUpdate = [object3, &angle]()
	{
		object3->transformation()->setAngleDegrees(angle);
		angle += 0.3f;
	};
	scene_->addObject(object4);
	scene_->addObject(object5);
	object1->transformation()->setPosition(glm::vec3(5.f, 0.f, 0.f));
	object2->transformation()->setPosition(glm::vec3(0.f, -5.f, 0.f));
	object3->transformation()->setPosition(glm::vec3(-5.f, 0.f, 0.f));
	object4->transformation()->setPosition(glm::vec3(0.f, 5.f, 0.f));
	object5->transformation()->setPosition(glm::vec3(0.f, 0.f, 5.f));
	camera_->setPosition(0, 0, 10);

	Light* light = new Light(glm::vec3(0, 0, 0));
	scene_->addLight(light);

	while (!glfwWindowShouldClose(window_))
	{
		auto start = std::chrono::system_clock::now();

		scene_->update();
		scene_->render(window_);
		glfwPollEvents();

		auto end = std::chrono::system_clock::now();
		chrono::milliseconds elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
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

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		camera_->moveForward();
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		camera_->moveLeft();
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		camera_->moveBackward();
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		camera_->moveRight();
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		camera_->rotateRight();
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		camera_->rotateLeft();
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		camera_->rotateUp();
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		camera_->rotateDown();
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
