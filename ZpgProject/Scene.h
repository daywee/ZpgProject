#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Scene
{
public:
	Scene();
	~Scene();

	void render(GLFWwindow*, GLuint shaderProgram);

private:
	const float points[9] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLuint vao_;
	GLuint vbo_;
};
