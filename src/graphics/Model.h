#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <graphics/Mesh.h>
#include <graphics/Texture2D.h>

#include <assimp/Importer.hpp>

class Model {
 public:
  Model(const unsigned int& usage, const std::vector<Mesh>& meshes,
        const std::vector<Texture2D>& textures)
      : usage(usage), meshes(meshes), textures(textures){};
  Model(const unsigned int& usage, const std::string& path);

  void init();
  void bind();
  void draw();
  void cleanup();
  std::vector<Mesh> getMeshes() const { return meshes; };
  std::vector<Texture2D> getTextures() const { return textures; };

 private:
  const unsigned int& usage;
  std::vector<Mesh> meshes;
  std::vector<Texture2D> textures;

  void processNode(aiNode* node, const aiScene* scene,
                   const std::string& directory);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene,
                   const std::string& directory);
  static std::vector<Texture2D> loadMaterialTextures(
      aiMaterial* mat, aiTextureType type, Texture2D::TextureType engineType,
      const std::string& directory);
};