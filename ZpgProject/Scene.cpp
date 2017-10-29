#include "Scene.h"


Scene::Scene(Shader* shader)
{
	shader_ = shader;
}

Scene::~Scene()
{
}

void Scene::render(GLFWwindow* window)
{
	// clear color and depth buffer
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for each (auto object in objects_)
	{
		object->draw(shader_);
	}

	for each (auto light in lights_)
	{
		light->draw(shader_);
	}

	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::addObject(Object* object)
{
	objects_.push_back(object);
}

void Scene::addLight(Light* light)
{
	lights_.push_back(light);
}

void Scene::notify(ISubject* subject)
{
	Camera* camera = static_cast<Camera*>(subject);
	useCamera(camera);
}

void Scene::useCamera(Camera* camera)
{
	shader_->useProgram();
	shader_->useProjectionMatrix(camera->getProjectionMatrix());
	shader_->useViewMatrix(camera->getViewMatrix());
	shader_->useCameraPosition(camera->getPosition());
	shader_->unuseProgram();
}
