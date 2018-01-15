#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <cstddef>
#include <cstdio>

Shader::Shader(const string vertexFile, const string fragmentFile)
{
	shaderLoader_ = new ShaderLoader();
	shaderProgram_ = shaderLoader_->loadShader(vertexFile.c_str(), fragmentFile.c_str());
	init();
}

Shader::Shader(ShaderType type)
{
	shaderLoader_ = new ShaderLoader();

	switch (type)
	{
	case BasicTexture:
		shaderProgram_ = shaderLoader_->loadShader("Shaders/Vertex/BasicTexture.glsl", "Shaders/Fragment/BasicTexture.glsl");
		break;
	case CubeMap:
		shaderProgram_ = shaderLoader_->loadShader("Shaders/Vertex/CubeMap.glsl", "Shaders/Fragment/CubeMap.glsl");
		break;
	case Phong:
		shaderProgram_ = shaderLoader_->loadShader("Shaders/Vertex/Phong.glsl", "Shaders/Fragment/Phong.glsl");
		break;
	case Universal:
	{
		std::stringstream message;
		message << "Universal shader does not exist." << endl;
		throw std::exception(message.str().c_str());
	}
	default: {
		std::stringstream message;
		message << "This shader type does not exist (" << static_cast<int>(type) << ")." << endl;
		throw std::exception(message.str().c_str());
	}
	}

	init();
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

void Shader::init()
{
	if (shaderProgram_ == 0)
	{
		std::stringstream message;
		message << "Cannot init() shader. ProgramId not set." << endl;
		throw std::exception(message.str().c_str());
	}

	modelMatrix_ = glGetUniformLocation(shaderProgram_, "modelMatrix");
	viewMatrix_ = glGetUniformLocation(shaderProgram_, "viewMatrix");
	projectionMatrix_ = glGetUniformLocation(shaderProgram_, "projectionMatrix");
	normalMatrix_ = glGetUniformLocation(shaderProgram_, "worldLightPosition");
	cameraPosition_ = glGetUniformLocation(shaderProgram_, "worldCameraPosition");
}

void Shader::useProjectionMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(projectionMatrix_, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::useMatrix(glm::mat4 matrix)
{
	glUniformMatrix4fv(modelMatrix_, 1, GL_FALSE, glm::value_ptr(matrix));
}
