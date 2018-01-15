#pragma once
#include <GL/glew.h>
#include "ShaderLoader.h"
#include <glm/glm.hpp>
#include "TextureLoader.h"

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
	void useCameraPosition(glm::vec3 position);

	// todo: remove !!! this is only temporary
	GLuint getProgram() const
	{
		return shaderProgram_;
	}

private:
	ShaderLoader* shaderLoader_;

	GLuint shaderProgram_;
	GLint modelMatrix_;
	GLint viewMatrix_;
	GLint projectionMatrix_;
	GLint normalMatrix_;
	GLint cameraPosition_;
	GLuint textureId_;
	TextureLoader* textureLoader_;
};
