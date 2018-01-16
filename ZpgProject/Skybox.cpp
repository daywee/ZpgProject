#include "Skybox.h"



Skybox::Skybox()
{
	auto tl = new TextureLoader();
	skybox_ = new Model("Models/Skybox/skybox.obj");
	textureId_ = tl->loadSkybox(
		"Models/Skybox/cubemap/negx.jpg",
		"Models/Skybox/cubemap/posx.jpg",
		"Models/Skybox/cubemap/negy.jpg",
		"Models/Skybox/cubemap/posy.jpg",
		"Models/Skybox/cubemap/negz.jpg",
		"Models/Skybox/cubemap/posz.jpg",
		69
	);

	delete tl;

	transformation()->setPosition(glm::vec3(0, 0, 0));
}


Skybox::~Skybox()
{
}

void Skybox::render(Shader* shader)
{
	shader->useProgram();
	shader->useMatrix(transformation()->matrix());
	skybox_->render(shader);
}
