#pragma once
#include <string>
#include <GL/glew.h>

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	GLuint load(std::string path);
	GLuint loadSkybox(std::string negX, std::string posX, std::string negY, std::string posY, std::string negZ, std::string posZ, GLuint textureUnit);
};

