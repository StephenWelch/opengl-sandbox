#include "Model.h"

void Model::init() {
  for (Texture2D& texture : textures) {
    texture.init();
  }
  mesh.init();
}

void Model::bind() {
  for (Texture2D& texture : textures) {
    texture.bind();
  }
  mesh.bind();
}

void Model::draw() { mesh.draw(); }

void Model::cleanup() {
  for (Texture2D& texture : textures) {
    texture.cleanup();
  }
  mesh.cleanup();
}

Mesh Model::getMesh() const { return mesh; }

std::vector<Texture2D> Model::getTextures() const { return textures; }
