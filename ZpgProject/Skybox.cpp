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
		0
	);

	delete tl;
}


Skybox::~Skybox()
{
}

void Skybox::render(Shader* shader)
{
	shader->useProgram();
	shader->useMatrix(transformation()->matrix());

	glActiveTexture(GL_TEXTURE0 + 0);
	glUniform1i(glGetUniformLocation(shader->getProgram(), "skybox"), 0);
	// And finally bind the texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId_);

	skybox_->render(shader);
}
