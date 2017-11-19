#pragma once
#include <string>
#include "LoadedObject.h"

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	LoadedObject* load(std::string fileName);
};

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};
