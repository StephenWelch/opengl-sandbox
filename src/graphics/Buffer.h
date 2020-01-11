#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <functional>

class Buffer {
 private:
  GLuint id;
  GLenum type;
  GLsizeiptr size;
  GLenum usage;

 public:
  Buffer(const GLenum& type) : type(type){};
  void init(const GLenum& usage, const GLsizeiptr& size);
  void cleanup();
  void bindShaderProgram(const GLuint& bindingIndex);
  void bind();
  void unbind();
  void execute(std::function<void(Buffer*)> operations);
  void setData(const void* data);
  GLuint getId() const;
  GLenum getUsage() const;
  void setUsage(const GLenum& usage);
  GLsizeiptr getSize() const;
  void setSize(const GLsizeiptr& size);
};

class UniformBuffer : public Buffer {
 public:
  UniformBuffer() : Buffer(GL_UNIFORM_BUFFER){};
};

class IndexBuffer : public Buffer {
 public:
  IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER){};
};

class VertexBuffer : public Buffer {
 public:
  VertexBuffer() : Buffer(GL_ARRAY_BUFFER){};
};
