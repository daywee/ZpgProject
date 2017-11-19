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

class Scene : public IObserver, public IUpdatable
{
public:
	Scene(Shader* shader);
	~Scene();

	void render(GLFWwindow*);
	void update() override;

	void registerRenderable(IRenderable* renderable);
	void registerUpdatable(IUpdatable* updatable);

	void notify(ISubject* subject) override;

private:
	vector<IRenderable*> renderables_;
	vector<IUpdatable*> updatables_;

	GLuint vao_;
	GLuint vbo_;
	Shader* shader_;

	void useCamera(Camera* camera);
};
