#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include "Updatable.h"
#include "Skybox.h"
class Scene : public IObserver, public IUpdatable
{
public:
	Scene(Shader* shader);
	~Scene();

	void render(GLFWwindow*) const;
	void update() override;

	void registerRenderable(IRenderable* renderable);
	void registerUpdatable(IUpdatable* updatable);

	void notify(ISubject* subject) override;

	void addSkybox(Shader* shader, Skybox* skybox);
	void addLight(Light* light);

private:
	vector<IRenderable*> renderables_;
	vector<IUpdatable*> updatables_;

	GLuint vao_;
	GLuint vbo_;
	Shader* shader_;
	Shader* skyboxShader_;
	Skybox* skybox_;
	vector<Light*> lights_;

	void useCamera(Camera* camera);
	void useSkyboxCamera(Camera* camera);
};
