#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <vector>
#include "Object.h"

class Scene
{
public:
	Scene();
	~Scene();

	void render(GLFWwindow*, Shader* shader);
	void addObject(Object* object);

private:
	vector<Object> objects_;

	GLuint vao_;
	GLuint vbo_;
};
