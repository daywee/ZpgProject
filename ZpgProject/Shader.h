#pragma once
#include <GL/glew.h>
#include "ShaderLoader.h"
#include <glm/glm.hpp>
#include "TextureLoader.h"
#include <vector>

enum ShaderType
{
	BasicTexture,
	CubeMap,
	Phong,
	PhongTexture,
	Common
};

class Light;

class Shader
{
public:
	Shader(const string vertexFile, const string fragmentFile);
	Shader(ShaderType type);
	~Shader();
	
	void checkStatus();
	void useProgram() const;
	void unuseProgram() const;
	void useMatrix(glm::mat4 matrix);
	void useViewMatrix(glm::mat4 matrix);
	void useProjectionMatrix(glm::mat4 matrix);
	void useLightPosition(glm::vec3 position);
	void useCameraPosition(glm::vec3 position);
	void useLights(std::vector<Light*> lights);

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
	GLint lightsCountId_;

	void init();
};
