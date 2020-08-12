#include "Buffer.h"

void Buffer::init(unsigned int usage, const GLsizeiptr& size)
{
		this->usage = usage;
		this->size = size;

		glCreateBuffers(1, &id);
		setData(nullptr);
}

void Buffer::cleanup() { glDeleteBuffers(1, &id); }

void Buffer::bindShaderProgram(unsigned int bindingIndex)
{
		glBindBufferBase(type, bindingIndex, id);
}

void Buffer::setData(const void* data)
{
		glNamedBufferData(id, size, data, usage);
}

void Buffer::setUsage(unsigned int usage) { this->usage = usage; }

void Buffer::setSize(const GLsizeiptr& size) { this->size = size; }
