#pragma once
#include "IRenderable.h"
#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include "Mesh.h"
#include "Transformable.h"
#include "Updatable.h"

class Model : public IRenderable, public Transformable, public Updatable
{
public:
	Model(GLchar *path);
	~Model();

	void render(Shader* shader) override;

private:
	std::vector<Mesh> meshes_;
	std::string directory_;
	std::vector<Texture> texturesLoaded_;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
										
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

};
