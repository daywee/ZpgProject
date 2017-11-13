#pragma once
#include <string>
#include <GL/glew.h>

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	GLuint load(std::string path, GLuint programId);
};

