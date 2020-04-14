#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <graphics/Mesh.h>
#include <graphics/Texture2D.h>

#include <assimp/Importer.hpp>

class Model {
public:
		Model(const unsigned int& usage, const std::vector<Mesh>& meshes)
						:usage(usage), meshes(meshes) { };
		Model(const unsigned int& usage, const std::string& path);

		void init();
		void draw();
		void cleanup();
		std::vector<Mesh> getMeshes() const { return meshes; };

private:
		const unsigned int& usage;
		std::vector<Mesh> meshes;

		void processNode(aiNode* node, const aiScene* scene,
						const std::string& directory);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene,
						const std::string& directory);
		static std::vector<Texture2D> loadMaterialTextures(
						aiMaterial* mat, aiTextureType type, Texture2D::TextureType engineType, unsigned int texture_unit_offset,
						const std::string& directory);
};