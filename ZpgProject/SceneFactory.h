#pragma once
#include "Scene.h"

class SceneFactory
{
public:
	static Scene* testScene(Camera* camera);
	static Scene* cubeScene(Camera* camera);
	static Scene* houseScene(Camera* camera);
};

