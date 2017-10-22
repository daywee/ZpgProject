#pragma once
#include <GL/glew.h>
#include "Transformation.h"
#include "Shader.h"
#include "Camera.h"
#include "Sphere.h"

class Object
{
public:
	Object();
	~Object();

	void draw(Shader* shader);

	Transformation* transformation();

	int getId();

private:
	static int nextId;

	int id_;

	GLuint vao_;
	GLuint vbo_;
	Transformation *transformation_;
};
