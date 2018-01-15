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

void Object::render(Shader* shader)
{
	shader->useProgram();
	shader->useMatrix(transformation()->matrix());

	switch (type_)
	{
	case Plain:
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader->getProgram(), "plainTexture"), 0);
		glBindTexture(GL_TEXTURE_2D, textureId_);

		glBindVertexArray(vao_);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		break;
	}
	case Sphere: renderInternal(sphereVertexCount); break;
	case SuziFlat: renderInternal(suziFlatVertexCount); break;
	case SuziSmooth: renderInternal(suziSmoothVertexCount); break;
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
	vao_ = 0;
	ebo_ = 0;

	glGenBuffers(1, &vbo_); // generate the VBO
	glGenVertexArrays(1, &vao_); // generate the vao
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_); // bind the vao

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW); // plain

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plainIndices), plainIndices, GL_STATIC_DRAW);


	// vertex attribute object(vao)

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));

	// normal vector
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	// texture maps
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind vbo
	glBindVertexArray(0); // unbind vao


	// texture
	//glGenTextures(1, &textureId_);
	//glBindTexture(GL_TEXTURE_2D, textureId_);

	//// set texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//// set texture filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	auto tl = new TextureLoader();
	textureId_ = tl->load("Textures/marble.bmp");
	delete tl;
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

void Object::renderInternal(int vertexCount, bool hasTexture)
{
	if (hasTexture)
	{
		glTexCoord2d(0.0, 1.0);
	}

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}
