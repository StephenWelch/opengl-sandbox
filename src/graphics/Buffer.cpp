#include "Buffer.h"

void Buffer::init()
{
  glGenBuffers(1, &id);
  bind();
  glBufferData(type, size, nullptr, GL_STATIC_DRAW);
  unbind();
}

void Buffer::cleanup()
{
  glDeleteBuffers(1, &id);
}

void Buffer::bindShaderProgram(const GLuint& bindingIndex) {
  bind();
  glBindBufferBase(type, bindingIndex, id);
  unbind();
}

void Buffer::bind()
{
  glBindBuffer(type, id);
}

void Buffer::unbind()
{
  glBindBuffer(type, 0);
}

void Buffer::execute(std::function<void(Buffer*)> operations)
{
  bind();
  operations(this);
  unbind();
}

void Buffer::setData(const void* data)
{
  glBufferData(type, size, data, usage);
}

GLuint Buffer::getId() const
{
  return id;
}
