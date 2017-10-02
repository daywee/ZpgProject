#include "Scene.h"
#include <cstddef>


Scene::Scene()
{
	//vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	//vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); //generate the vao
	glBindVertexArray(vao_); //bind the vao
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

Scene::~Scene()
{
}

void Scene::render(GLFWwindow* window, GLuint shaderProgram)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glBindVertexArray(vao_);
	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
									  // update other events like input handling
	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}
