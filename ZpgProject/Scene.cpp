#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::render(GLFWwindow* window, Shader* shader)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->useProgram();
	
	for each (auto object in objects_)
	{
		object.bindVertexArray();
		shader->useMatrix(object.getTransformationMatrix());
		object.draw();
	}

	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::addObject(Object* object)
{
	objects_.push_back(*object);
}
