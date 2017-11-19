#include "Object.h"
#include <algorithm>
#include "SuziFlat.h"
#include "SuziSmooth.h"
#include "Plain.h"
#include "Sphere.h"

int Object::nextId = 0;

Object::Object(ObjectType type)
{
	id_ = nextId++;
	transformation_ = new Transformation();
	type_ = type;

	switch (type)
	{
	case Plain: initPlain(); break;
	case Sphere: initSphere(); break;
	case SuziFlat: initSuziFlat(); break;
	case SuziSmooth: initSuziSmooth(); break;
	default: throw std::exception("Uknown object type");
	}
}

Object::~Object()
{
}

void Object::render(Shader* shader) // todo: rename to render
{
	shader->useProgram();
	shader->useMatrix(transformation()->matrix());

	switch (type_)
	{
	case Plain: drawInternal(plainVertexCount, true); break;
	case Sphere: drawInternal(sphereVertexCount); break;
	case SuziFlat: drawInternal(suziFlatVertexCount); break;
	case SuziSmooth: drawInternal(suziSmoothVertexCount); break;
	default: throw std::exception("Uknown object type");
	}

	shader->unuseProgram();
}

Transformation* Object::transformation()
{
	return transformation_;
}

int Object::getId()
{
	return id_;
}

void Object::initPlain()
{
	// vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW); // sphere
	//glBufferData(GL_ARRAY_BUFFER, sizeof(suziFlat), suziFlat, GL_STATIC_DRAW); // suzi flat
	//glBufferData(GL_ARRAY_BUFFER, sizeof(suziSmooth), suziSmooth, GL_STATIC_DRAW); // suzi smooth
	glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW); // plain

	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));

	// normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	// texture maps
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::initSphere()
{
	// vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW); // sphere
	//glBufferData(GL_ARRAY_BUFFER, sizeof(suziFlat), suziFlat, GL_STATIC_DRAW); // suzi flat
	//glBufferData(GL_ARRAY_BUFFER, sizeof(suziSmooth), suziSmooth, GL_STATIC_DRAW); // suzi smooth
	//glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW); // plain

	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));

	// normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::initSuziFlat()
{
	// vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(suziFlat), suziFlat, GL_STATIC_DRAW); // suzi flat

	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));

	// normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::initSuziSmooth()
{
	// vertex buffer object (VBO)
	vbo_ = 0;
	glGenBuffers(1, &vbo_); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(suziSmooth), suziSmooth, GL_STATIC_DRAW); // suzi smooth

	// vertex attribute object(vao)
	vao_ = 0;
	glGenVertexArrays(1, &vao_); // generate the vao
	glBindVertexArray(vao_); // bind the vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));

	// normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::drawInternal(int vertexCount, bool hasTexture)
{
	if (hasTexture)
	{
		glTexCoord2d(0.0, 1.0);
	}

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}
