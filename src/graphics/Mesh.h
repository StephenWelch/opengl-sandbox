#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Buffer.h>

#include <glm/glm.hpp>
#include <vector>

class Mesh {
 private:
  struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
  };

  const GLint VERTEX_SIZE = 3;
  const GLint NORMAL_SIZE = 3;
  const GLint TEX_COORD_SIZE = 2;

  GLenum usage;
  std::vector<Vertex> vertexData;
  std::vector<GLuint> indexData;
  GLuint vao;
  VertexBuffer vbo;
  IndexBuffer ebo;

 public:
  Mesh(const GLenum& usage, const std::vector<glm::vec3>& vertices,
       const std::vector<glm::vec3> normals,
       const std::vector<glm::vec2>& textureCoords,
       const std::vector<GLuint>& indices);
  Mesh(const GLenum& usage, const std::vector<Vertex>& vertices,
       const std::vector<GLuint>& indices);

  void init();
  void bind();
  void draw();
  void cleanup();
};