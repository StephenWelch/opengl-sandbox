#include "Model.h"

void Model::processNode(aiNode* node, const aiScene* scene,
				const std::string& directory)
{
		for (unsigned int i = 0; i<node->mNumMeshes; i++) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(processMesh(mesh, scene, directory));
		}
		for (unsigned int i = 0; i<node->mNumChildren; i++) {
				processNode(node->mChildren[i], scene, directory);
		}
}

std::vector<Texture> Model::loadMaterialTextures(
				aiMaterial* mat, aiTextureType type, Texture::TextureType engineType, unsigned int texture_unit_offset,
				const std::string& directory)
{
		std::vector<Texture> loadedTextures;
		for (unsigned int i = 0; i<mat->GetTextureCount(type); i++) {
				aiString str;
				mat->GetTexture(type, i, &str);
				Texture texture(engineType, directory+"/"+std::string(str.C_Str()), texture_unit_offset + i + GL_TEXTURE0);
				loadedTextures.push_back(texture);
		}
		return loadedTextures;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene,
				const std::string& directory)
{
		std::vector<Mesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
				Mesh::Vertex vertex{};
				vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y,
												 mesh->mNormals[i].z};
				vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y,
													 mesh->mVertices[i].z};
				if (mesh->mTextureCoords[0]) {
						vertex.texCoords = {mesh->mTextureCoords[0][i].x,
																mesh->mTextureCoords[0][i].y};
				} else {
						vertex.texCoords = {0.0f, 0.0f};
				}

				// TODO Tangents and Bitangents

				vertices.push_back(vertex);
		}

		for (unsigned int faceIndex = 0; faceIndex<mesh->mNumFaces; faceIndex++) {
				aiFace face = mesh->mFaces[faceIndex];
				for (unsigned int indexIndex = 0; indexIndex<face.mNumIndices;
						 indexIndex++) {
						indices.push_back(face.mIndices[indexIndex]);
				}
		}

//		if (mesh->mMaterialIndex>=0) {
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<Texture> textures;
				std::vector<Texture> diffuseMaps =
								loadMaterialTextures(material, aiTextureType_DIFFUSE,
												Texture::TextureType::DIFFUSE, textures.size(), directory);
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
				std::vector<Texture> specularMaps =
								loadMaterialTextures(material, aiTextureType_SPECULAR,
												Texture::TextureType::SPECULAR, textures.size(), directory);
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
				std::vector<Texture> emissiveMaps =
								loadMaterialTextures(material, aiTextureType_EMISSIVE,
												Texture::TextureType::EMISSIVE, textures.size(), directory);
				textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());

				// TODO Heightmaps

//		}

		return Mesh(usage, vertices, indices, textures);
}

Model::Model(const unsigned int& usage, const std::string& path)
				:usage(usage)
{
		Assimp::Importer importer;
		const auto* scene =
						importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		ENGINE_ASSERT(
						scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode,
						"Error loading model with Assimp: ", importer.GetErrorString())

		processNode(scene->mRootNode, scene, path.substr(0, path.find_last_of('/')));
}

void Model::init()
{
		for (auto& mesh : meshes) {
				mesh.init();
		}
}

void Model::draw()
{
		for (auto& mesh : meshes) {
				mesh.bind();
				mesh.draw();
		}
}

void Model::cleanup()
{
		for (auto& mesh : meshes) {
				mesh.cleanup();
		}
}
