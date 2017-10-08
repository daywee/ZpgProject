#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"

class Object
{
public:
	Object();
	~Object();

	void bindVertexArray();
	void draw();

	void setPosition(glm::vec3 position);
	void setSize(glm::vec3 size);
	void setAngle(float angle);

	glm::mat4 getTransformationMatrix();
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
