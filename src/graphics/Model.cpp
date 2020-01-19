#include "Model.h"

#include <algorithm>

void Model::processNode(aiNode* node, const aiScene* scene,
                        const std::string& directory) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene, directory));
  }
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene, directory);
  }
}

std::vector<Texture2D> Model::loadMaterialTextures(
    aiMaterial* mat, aiTextureType type, Texture2D::TextureType engineType,
    const std::string& directory) {
  std::vector<Texture2D> loadedTextures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    // Check texture UID is not already loaded
    aiString str;
    mat->GetTexture(type, i, &str);
    Texture2D texture(engineType, directory + std::string(str.C_Str()), 0);
    loadedTextures.push_back(texture);
  }
  return loadedTextures;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene,
                        const std::string& directory) {
  std::vector<Mesh::Vertex> vertices;
  std::vector<unsigned int> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Mesh::Vertex vertex;
    vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y,
                     mesh->mNormals[i].z};
    vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y,
                       mesh->mVertices[i].z};
    if (mesh->mTextureCoords[0]) {
      vertex.texCoords = {mesh->mTextureCoords[0][i].x,
                          mesh->mTextureCoords[0][i].y};
    }
    vertices.push_back(vertex);
  }

  for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
    aiFace face = mesh->mFaces[faceIndex];
    for (unsigned int indexIndex = 0; indexIndex < face.mNumIndices;
         indexIndex++) {
      indices.push_back(face.mIndices[indexIndex]);
    }
  }

  if (mesh->mMaterialIndex >= 0) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture2D> diffuseMaps =
        loadMaterialTextures(material, aiTextureType_DIFFUSE,
                             Texture2D::TextureType::DIFFUSE, directory);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture2D> specularMaps =
        loadMaterialTextures(material, aiTextureType_SPECULAR,
                             Texture2D::TextureType::SPECULAR, directory);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture2D> emissiveMaps =
        loadMaterialTextures(material, aiTextureType_EMISSIVE,
                             Texture2D::TextureType::EMISSIVE, directory);
    textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
  }

  return Mesh(usage, vertices, indices);
}

Model::Model(const unsigned int& usage, const std::string& path)
    : usage(usage) {
  Assimp::Importer importer;
  const auto* scene =
      importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  ENGINE_ASSERT(
      scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode,
      "Error loading model with Assimp: {}", importer.GetErrorString());

  processNode(scene->mRootNode, scene, path.substr(0, path.find_last_of('/')));
}

void Model::init() {
  for (auto& texture : textures) {
    texture.init();
  }
  for (auto& mesh : meshes) {
    mesh.init();
  }
}

void Model::bind() {
  for (auto& texture : textures) {
    texture.bind();
  }
  for (auto& mesh : meshes) {
    mesh.bind();
  }
}

void Model::draw() {
  for (auto& mesh : meshes) {
    mesh.draw();
  }
}

void Model::cleanup() {
  for (auto& texture : textures) {
    texture.cleanup();
  }
  for (auto& mesh : meshes) {
    mesh.cleanup();
  }
}
