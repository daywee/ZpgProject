#pragma once
#include <GL/glew.h>
#include "Transformation.h"
#include "Shader.h"
#include "IRenderable.h"
#include "Updatable.h"
#include "Transformable.h"

enum ObjectType
{
	Plain,
	Sphere,
	SuziFlat,
	SuziSmooth
};

class Object : public IRenderable, public Updatable, public Transformable
{
public:
	Object(ObjectType type);
	~Object();

	void render(Shader* shader) override;

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
