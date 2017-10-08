#pragma once
#include <GL/glew.h>
#include "ShaderLoader.h"
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const string vertexFile, const string fragmentFile);
	~Shader();
	
	void checkStatus();
	void useProgram() const;
	void useMatrix(glm::mat4 matrix) const;

private:
	ShaderLoader* shaderLoader_;

	GLuint shaderProgram_;
	GLint modelTransform_;
};
