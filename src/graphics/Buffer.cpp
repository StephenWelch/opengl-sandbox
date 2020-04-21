#include "Buffer.h"

void Buffer::init(const GLenum& usage, const GLsizeiptr& size)
{
		this->usage = usage;
		this->size = size;

		glCreateBuffers(1, &id);
		setData(nullptr);
}

void Buffer::cleanup() { glDeleteBuffers(1, &id); }

void Buffer::bindShaderProgram(const GLuint& bindingIndex)
{
		glBindBufferBase(type, bindingIndex, id);
}

void Buffer::setData(const void* data)
{
		glNamedBufferData(id, size, data, usage);
}

GLuint Buffer::getId() const { return id; }

GLenum Buffer::getUsage() const { return usage; }

void Buffer::setUsage(const GLenum& usage) { this->usage = usage; }

GLsizeiptr Buffer::getSize() const { return size; }

void Buffer::setSize(const GLsizeiptr& size) { this->size = size; }
