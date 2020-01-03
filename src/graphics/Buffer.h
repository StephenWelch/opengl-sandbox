#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

class Buffer {
private:
  GLuint id;
  GLenum type;
  GLsizeiptr size;
  GLenum usage;
public:
  Buffer(const GLenum type, const GLenum& usage, const GLsizeiptr& size) : type(type), usage(usage), size(size) {};
  void init();
  void cleanup();
  void bindShaderProgram(const GLuint& bindingIndex);
  void bind();
  void unbind();
  void execute(std::function<void(Buffer*)> operations);
  void setData(const void* data);
  GLuint getId() const;
};

class UniformBuffer : public Buffer {
public:
  UniformBuffer(const GLenum& usage, const GLsizeiptr& size) : Buffer(GL_UNIFORM_BUFFER, usage, size) {};
};