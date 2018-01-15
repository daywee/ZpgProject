#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <assimp/types.h>
#include "IRenderable.h"

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	string type;
	aiString path;
};

class Mesh : public IRenderable
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

	void render(Shader* shader) override;

private:
	/*  Mesh Data  */
	vector<Vertex> vertices_;
	vector<GLuint> indices_;
	vector<Texture> textures_;

	GLuint VAO_, VBO_, EBO_;

	void setupMesh();
};
