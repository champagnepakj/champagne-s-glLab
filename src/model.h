#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include "mesh.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <../Dependencies/GLM/glm.hpp>
#include <../Dependencies/GLM/gtc/matrix_transform.hpp>
#include <../Dependencies/GLM/gtc/type_ptr.hpp>
#include "../shaders/shader.h"
#include <glad/glad.h>
#include "stb/stb_image.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);


class Model
{
	public:
		std::vector<Texture> textures_loaded;
		Model(const char* path) // USED TO BE Model(char* path)
		{
			loadModel(path);
		}
		void Draw(Shader& shader)
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
				meshes[i].Draw(shader);
		}

	private:
		// model data
		std::vector<Mesh> meshes;
		std::string directory;

		void loadModel(std::string path)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR:ASSIMP::" << import.GetErrorString() << std::endl;
				return;
			}
			directory = path.substr(0, path.find_last_of('/'));

			processNode(scene->mRootNode, scene);
		}
		void processNode(aiNode* node, const aiScene* scene)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(processMesh(mesh, scene));
			}
			// then do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}
		Mesh processMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Texture> textures;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				// process vertex positions, normals, and texture coordinates
				glm::vec3 vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.Position = vector;
				if (mesh->HasNormals())
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
					vertex.Normal = vector;
				}
				// Texture coordinatres
				if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					glm::vec2 vec;
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y; // CHECK THIS FOR FUCKED TEXTURES
					vertex.TexCoords = vec;
				}
				else
					vertex.TexCoords = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// diffuse: texture_diffuseN
			// specular: texture_specularN
			// normal: texture_normalN

			// 1. diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. normal maps
			std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. height maps
			std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());




			return Mesh(vertices, indices, textures);
		}
	
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
		{
			std::vector<Texture> textures;
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
				bool skip = false;
				for (unsigned int j = 0; j < textures_loaded.size(); j++)
				{
					if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
					{
						textures.push_back(textures_loaded[j]);
						skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
						break;
					}
				}
				if (!skip)
				{   // if texture hasn't been loaded already, load it
					Texture texture;
					texture.id = TextureFromFile(str.C_Str(), this->directory);
					texture.type = typeName;
					texture.path = str.C_Str();
					textures.push_back(texture);
					textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
				}
			}
			return textures;
		}

};

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else if(!data)
	{
		std::cout << "Failed to load texture at path: " << filename << std::endl;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	

	


	return textureID;
}
