#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::render(GLFWwindow* window, Shader* shader, Camera* camera)
{
	// clear color and depth buffer
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for each (auto object in objects_)
	{
		object.draw(shader, camera);
	}

	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::addObject(Object* object)
{
	objects_.push_back(*object);
}
