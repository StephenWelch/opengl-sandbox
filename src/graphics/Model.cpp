#include "Model.h"

void Model::processNode(aiNode *node, const aiScene *scene,
												const std::filesystem::path &directory) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene, directory));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, directory);
	}
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(
		aiMaterial *mat, aiTextureType type, Texture::TextureType engineType, unsigned int texture_unit_offset,
		const std::filesystem::path &directory) {
	std::vector<std::shared_ptr<Texture>> loadedTextures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		auto texture = std::make_shared<Texture2d>(engineType,
																							 texture_unit_offset + i,
																							 directory.generic_string() + "/" + std::string(str.C_Str()));
		loadedTextures.push_back(texture);
	}
	return loadedTextures;
}

std::shared_ptr<Mesh> Model::processMesh(aiMesh *mesh, const aiScene *scene,
																				 const std::filesystem::path &directory) {
	std::vector<TexturedMesh::Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		TexturedMesh::Vertex vertex{};
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

	for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
		aiFace face = mesh->mFaces[faceIndex];
		for (unsigned int indexIndex = 0; indexIndex < face.mNumIndices;
				 indexIndex++) {
			indices.push_back(face.mIndices[indexIndex]);
		}
	}

//		if (mesh->mMaterialIndex>=0) {
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<std::shared_ptr<Texture>> diffuseMaps =
			loadMaterialTextures(material, aiTextureType_DIFFUSE,
													 Texture::TextureType::DIFFUSE, textures.size(), directory);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<std::shared_ptr<Texture>> specularMaps =
			loadMaterialTextures(material, aiTextureType_SPECULAR,
													 Texture::TextureType::SPECULAR, textures.size(), directory);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	std::vector<std::shared_ptr<Texture>> emissiveMaps =
			loadMaterialTextures(material, aiTextureType_EMISSIVE,
													 Texture::TextureType::EMISSIVE, textures.size(), directory);
	textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());

	// TODO Heightmaps

//		}

	return std::make_shared<TexturedMesh>(usage, vertices, indices, textures);
}

Model::Model(unsigned int usage, const std::filesystem::path &path)
		: usage(usage) {
	Assimp::Importer importer;
	const auto *scene =
			importer.ReadFile(path.generic_string(), aiProcess_Triangulate | aiProcess_FlipUVs);

	ENGINE_ASSERT(
			scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode,
			"Error loading model with Assimp: ", importer.GetErrorString())

	processNode(scene->mRootNode, scene, path.parent_path());
}

void Model::init() {
	for (auto &mesh : meshes) {
		mesh->init();
	}
}

void Model::draw() {
	for (auto &mesh : meshes) {
		mesh->bind();
		mesh->draw();
	}
}

void Model::cleanup() {
	for (auto &mesh : meshes) {
		mesh->cleanup();
	}
}
