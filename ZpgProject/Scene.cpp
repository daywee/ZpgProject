#include "Scene.h"


Scene::Scene(Shader* shader)
{
	shader_ = shader;
}

Scene::~Scene()
{
}

void Scene::render(GLFWwindow* window) const
{
	// clear color and depth buffer
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox_->render(skyboxShader_);
	glClear(GL_DEPTH_BUFFER_BIT);

	for each (auto renderable in renderables_)
	{
		renderable->render(shader_);
	}

	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::update()
{
	for each (auto updatable in updatables_)
	{
		updatable->update();
	}
}

void Scene::registerRenderable(IRenderable* renderable)
{
	renderables_.push_back(renderable);
}

void Scene::registerUpdatable(IUpdatable* updatable)
{
	updatables_.push_back(updatable);
}

void Scene::notify(ISubject* subject)
{
	Camera* camera = static_cast<Camera*>(subject);
	useCamera(camera);
	useSkyboxCamera(camera);
}

void Scene::addSkybox(Shader* shader, Skybox* skybox)
{
	skyboxShader_ = shader;
	skybox_ = skybox;
}

void Scene::useCamera(Camera* camera)
{
	shader_->useProgram();

	shader_->useProjectionMatrix(camera->getProjectionMatrix());
	shader_->useViewMatrix(camera->getViewMatrix());
	shader_->useCameraPosition(camera->getPosition());

	shader_->unuseProgram();
}

void Scene::useSkyboxCamera(Camera* camera)
{
	skyboxShader_->useProgram();

	skybox_->transformation()->setPosition(camera->getPosition());
	skyboxShader_->useProjectionMatrix(camera->getProjectionMatrix());
	skyboxShader_->useViewMatrix(camera->getViewMatrix());

	skyboxShader_->unuseProgram();
}
