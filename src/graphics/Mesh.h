#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Buffer.h>

#include <glm/glm.hpp>
#include <vector>

class Mesh {
 public:
  struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
  };

  Mesh(const unsigned int& usage, const std::vector<glm::vec3>& vertices,
       const std::vector<glm::vec3> normals,
       const std::vector<glm::vec2>& textureCoords,
       const std::vector<unsigned int>& indices);
  Mesh(const unsigned int& usage, const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices);

  void init();
  void bind();
  void draw();
  void cleanup();
 private:
  const int VERTEX_SIZE = 3;
  const int NORMAL_SIZE = 3;
  const int TEX_COORD_SIZE = 2;

  unsigned int usage;
  std::vector<Vertex> vertexData;
  std::vector<unsigned int> indexData;
  unsigned int vao;
  VertexBuffer vbo;
  IndexBuffer ebo;
};