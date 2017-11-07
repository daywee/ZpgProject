#pragma once
#include <string>

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	void load(std::string path);
};

