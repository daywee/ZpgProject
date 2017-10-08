#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>
#include <cstdio>

Shader::Shader(const string vertexFile, const string fragmentFile)
{
	shaderLoader_ = new ShaderLoader();
	shaderProgram_ = shaderLoader_->loadShader(vertexFile.c_str(), fragmentFile.c_str());
	modelTransform_ = glGetUniformLocation(shaderProgram_, "trasfromMatrix");
}

Shader::~Shader()
{
	shaderLoader_->deleteShader();
	delete shaderLoader_;
}

void Shader::checkStatus()
{
	GLint status;
	glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram_, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram_, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void Shader::useProgram() const
{
	glUseProgram(shaderProgram_);
}

void Shader::useMatrix(glm::mat4 matrix) const
{
	glUniformMatrix4fv(modelTransform_, 1, GL_FALSE, glm::value_ptr(matrix)); //location, count, transpose, *value
}
