#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <graphics/Mesh.h>
#include <graphics/Texture.h>

#include <assimp/Importer.hpp>

class Model {
public:
		Model(const unsigned int& usage, const std::vector<Mesh>& meshes)
						:usage(usage), meshes(meshes) { };
		Model(const unsigned int& usage, const std::string& path);

		void init();
		void draw();
		void cleanup();
		void setPosition(const glm::vec3& position) { this->position = position; };
		void setRotation(const glm::vec3& rotation) { this->rotation = rotation; };
		void setScale(const glm::vec3& scale) { this->scale = scale; };
		void setScale(float scale) { this-> scale = glm::vec3(scale); };
		auto getMeshes() const { return meshes; };
		auto getPosition() const { return this->position; };
		auto getRotation() const { return this->rotation; };
		auto getScale() const { return this->scale; };

private:
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		const unsigned int& usage;
		std::vector<Mesh> meshes;

		void processNode(aiNode* node, const aiScene* scene,
						const std::string& directory);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene,
						const std::string& directory);
		static std::vector<Texture> loadMaterialTextures(
						aiMaterial* mat, aiTextureType type, Texture::TextureType engineType, unsigned int texture_unit_offset,
						const std::string& directory);
};