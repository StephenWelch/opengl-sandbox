#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Mesh {
private:
  const GLint VERTEX_SIZE = 3;
  const GLint NORMAL_SIZE = 3;
  const GLint TEX_COORD_SIZE = 2;
  const GLint VERTEX_ATTRIB_SIZE = 8;

  GLenum usage;
  std::vector<float> modelData;
  std::vector<int> indexData;
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
public:
  Mesh(const GLenum& usage, const std::vector<float>& vertices, const std::vector<float> normals, const std::vector<float>& textureCoords, const std::vector<int>& indices);
  void init();
  void bind();
  void draw();
  void cleanup();
};