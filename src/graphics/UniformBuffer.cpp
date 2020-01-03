#include "UniformBuffer.h"
#include "UniformBuffer.h"
#include "UniformBuffer.h"

void UniformBuffer::init()
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_UNIFORM_BUFFER, id);
  glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::cleanup()
{
  glDeleteBuffers(1, &id);
}

void UniformBuffer::bindShaderProgram(const GLuint& bindingIndex) {
  glBindBuffer(GL_UNIFORM_BUFFER, id);
  glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, id);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::setData(const void* data)
{
  glBindBuffer(GL_UNIFORM_BUFFER, id);
  glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint UniformBuffer::getId() const
{
  return id;
}
