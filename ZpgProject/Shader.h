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
	void unuseProgram() const;
	void useMatrix(glm::mat4 matrix);
	void useViewMatrix(glm::mat4 matrix);
	void useProjectionMatrix(glm::mat4 matrix);
	void useLightPosition(glm::vec3 position);

private:
	ShaderLoader* shaderLoader_;

	GLuint shaderProgram_;
	GLint modelMatrix_;
	GLint viewMatrix_;
	GLint projectionMatrix_;
	GLint normalMatrix_;
};
