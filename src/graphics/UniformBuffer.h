#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UniformBuffer {
private:
  GLuint id;
  GLsizeiptr size;
  GLenum usage;
public:
  UniformBuffer(const GLenum& usage, const GLsizeiptr& size) : usage(usage), size(size) {};
  void init();
  void cleanup();
  void bindShaderProgram(const GLuint& bindingIndex);
  void setData(const void* data);
  GLuint getId() const;
};