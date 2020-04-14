#include "Buffer.h"

void Buffer::init(const GLenum& usage, const GLsizeiptr& size)
{
		this->usage = usage;
		this->size = size;

		glGenBuffers(1, &id);
		bind();
		glBufferData(type, size, nullptr, GL_STATIC_DRAW);
		unbind();
}

void Buffer::cleanup() { glDeleteBuffers(1, &id); }

void Buffer::bindShaderProgram(const GLuint& bindingIndex)
{
		bind();
		glBindBufferBase(type, bindingIndex, id);
		unbind();
}

void Buffer::bind() { glBindBuffer(type, id); }

void Buffer::unbind() { glBindBuffer(type, 0); }

void Buffer::execute(const std::function<void(Buffer*)>& operations)
{
		bind();
		operations(this);
		unbind();
}

void Buffer::setData(const void* data)
{
		glBufferData(type, size, data, usage);
}

GLuint Buffer::getId() const { return id; }

GLenum Buffer::getUsage() const { return usage; }

void Buffer::setUsage(const GLenum& usage) { this->usage = usage; }

GLsizeiptr Buffer::getSize() const { return size; }

void Buffer::setSize(const GLsizeiptr& size) { this->size = size; }
