#pragma once

#include <graphics/Mesh.h>
#include <graphics/Texture2D.h>

class Model {
 private:
  Mesh mesh;
  std::vector<Texture2D> textures;

 public:
  Model(const Mesh& mesh, const std::vector<Texture2D> textures)
      : mesh(mesh), textures(textures){};
  void init();
  void bind();
  void draw();
  void cleanup();
  Mesh getMesh() const;
  std::vector<Texture2D> getTextures() const;
};