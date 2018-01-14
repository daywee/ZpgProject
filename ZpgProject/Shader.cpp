#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>
#include <cstdio>
#include "TextureLoader.h"

Shader::Shader(const string vertexFile, const string fragmentFile)
{
	shaderLoader_ = new ShaderLoader();
	shaderProgram_ = shaderLoader_->loadShader(vertexFile.c_str(), fragmentFile.c_str());
	modelMatrix_ = glGetUniformLocation(shaderProgram_, "modelMatrix");
	viewMatrix_ = glGetUniformLocation(shaderProgram_, "viewMatrix");
	projectionMatrix_ = glGetUniformLocation(shaderProgram_, "projectionMatrix");
	normalMatrix_ = glGetUniformLocation(shaderProgram_, "worldLightPosition");
	cameraPosition_ = glGetUniformLocation(shaderProgram_, "worldCameraPosition");
	textureLoader_ = new TextureLoader();
	textureId_ = textureLoader_->load("Models/House/house.png");
}

Shader::~Shader()
{
	shaderLoader_->deleteShader();
	delete shaderLoader_;
	delete textureLoader_;
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

void Shader::unuseProgram() const
{
	glUseProgram(0);
}

void Shader::useViewMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(viewMatrix_, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::useLightPosition(glm::vec3 position)
{
	glProgramUniform3f(shaderProgram_, normalMatrix_, position.x, position.y, position.z);
}

void Shader::useCameraPosition(glm::vec3 position)
{
	glProgramUniform3f(shaderProgram_, cameraPosition_, position.x, position.y, position.z);
}

void Shader::useProjectionMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(projectionMatrix_, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::useMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(modelMatrix_, 1, GL_FALSE, glm::value_ptr(matrix));
}
