#pragma once
#include <string>

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

private:
	void load(std::string fileName);
};

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};
