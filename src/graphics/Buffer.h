#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <functional>

class Buffer {
 private:
	unsigned int id;
	unsigned int type;
	unsigned int usage;
	GLsizeiptr size;

 public:
	explicit Buffer(const GLenum &type)
			: type(type) {};

	void init(unsigned int usage, const GLsizeiptr &size);
	void cleanup();
	void bindShaderProgram(unsigned int bindingIndex);

	void setData(const void *data);
	auto getId() const { return id; }
	auto getUsage() const { return usage; }
	void setUsage(unsigned int usage);
	auto getSize() const { return size; }
	void setSize(const GLsizeiptr &size);
};

class UniformBuffer : public Buffer {
 public:
	UniformBuffer()
			: Buffer(GL_UNIFORM_BUFFER) {};
};

class IndexBuffer : public Buffer {
 public:
	IndexBuffer()
			: Buffer(GL_ELEMENT_ARRAY_BUFFER) {};
};

class VertexBuffer : public Buffer {
 public:
	VertexBuffer()
			: Buffer(GL_ARRAY_BUFFER) {};
};
