#pragma once
#include <GL/glew.h>
#include "Transformation.h"
#include "Shader.h"
#include "Camera.h"

class Object
{
public:
	Object();
	~Object();

	void draw(Shader* shader);

	Transformation* transformation();

	glm::mat4 transformationMatrix();
	int getId();

private:
	static int nextId;

	int id_;

	const float points_[9] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLuint vao_;
	GLuint vbo_;
	Transformation *transformation_;
};
