#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Mesh {
private:
  const int VERTEX_ATTRIB_SIZE = 5;

  GLenum usage;
  std::vector<float> modelData;
  std::vector<int> indexData;
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
public:
  Mesh(const GLenum& usage, const std::vector<float>& vertices, const std::vector<float>& textureCoords, const std::vector<int>& indices);
  void init();
  void bind();
  void draw();
  void cleanup();
};