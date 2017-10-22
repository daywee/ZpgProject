#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

class Scene : public IObserver
{
public:
	Scene(Shader* shader);
	~Scene();

	void render(GLFWwindow*);
	void addObject(Object* object);
	void addLight(Light* light);

	void notify(ISubject* subject) override;

private:
	vector<Object> objects_;
	vector<Light> lights_;

	GLuint vao_;
	GLuint vbo_;
	Shader* shader_;

	void useCamera(Camera* camera);
};
