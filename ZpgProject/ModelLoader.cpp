#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <glm/detail/type_vec4.hpp>


ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

LoadedObject* ModelLoader::load(std::string fileName)
{
	GLuint vao, vbo, ibo;
	int indicesCount = 0;

	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slou?ení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodn? duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy


												//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(fileName, importOptions);

	if (scene)
	{
		// pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);

			aiString path;
			if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				auto textureLoader = new TextureLoader();
				GLuint id = textureLoader->load("Models/House/" + string(path.C_Str()));
			}

		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
		{
			aiMesh* mesh = scene->mMeshes[i];

			Vertex* pVertices = new Vertex[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(Vertex)* mesh->mNumVertices);

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				if (mesh->HasPositions())
				{
					pVertices[i].Position[0] = mesh->mVertices[i].x;
					pVertices[i].Position[1] = mesh->mVertices[i].y;
					pVertices[i].Position[2] = mesh->mVertices[i].z;
				}
				if (mesh->HasNormals())
				{
					pVertices[i].Normal[0] = mesh->mNormals[i].x;
					pVertices[i].Normal[1] = mesh->mNormals[i].y;
					pVertices[i].Normal[2] = mesh->mNormals[i].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
					pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					pVertices[i].Tangent[0] = mesh->mTangents[i].x;
					pVertices[i].Tangent[1] = mesh->mTangents[i].y;
					pVertices[i].Tangent[2] = mesh->mTangents[i].z;
				}

			}

			unsigned int* pIndices = nullptr;

			if (mesh->HasFaces())
			{

				pIndices = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int i = 0; i < mesh->mNumFaces; i++)
				{
					pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
					pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
				}
			}


			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ibo);

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(vao);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::stringstream message;
				message << "GL ERROR: " << err << endl;
				throw exception(message.str().c_str());
			} 
			indicesCount = mesh->mNumFaces * 3;

			delete[] pVertices;
			delete[] pIndices;
		}
	}
	else
	{
		std::stringstream message;
		message << "Error during parsing mesh from " << fileName << " : " << importer.GetErrorString() << endl;
		throw std::exception(message.str().c_str());
	}
	glBindVertexArray(0);

	return new LoadedObject(indicesCount, vao, vbo, ibo);
}
