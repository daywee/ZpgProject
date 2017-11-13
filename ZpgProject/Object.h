#pragma once
#include <GL/glew.h>
#include "Transformation.h"
#include "Shader.h"
#include "Camera.h"
#include "Sphere.h"

enum ObjectType
{
	Plain,
	Sphere,
	SuziFlat,
	SuziSmooth
};

class Object
{
public:
	Object(ObjectType type);
	~Object();

	void draw(Shader* shader);

	Transformation* transformation();

	int getId();

private:
	static int nextId;

	int id_;
	ObjectType type_;

	GLuint vao_;
	GLuint vbo_;
	Transformation *transformation_;

	void initPlain();
	void initSphere();
	void initSuziFlat();
	void initSuziSmooth();

	void drawInternal(int vertexCount, bool texture = false);
};
