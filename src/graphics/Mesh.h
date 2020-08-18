#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Buffer.h>
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"

class Mesh {
 public:
	virtual void init() = 0;
	virtual void bind() = 0;
	virtual void draw() = 0;
	virtual void cleanup() = 0;

	virtual std::vector<std::shared_ptr<Texture>> getTextures() = 0;
};

class TexturedMesh : public virtual Mesh {
public:
		struct Vertex {
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texCoords;
		};

		TexturedMesh(unsigned int usage, const std::vector<glm::vec3>& vertices,
						const std::vector<glm::vec3>& normals,
						const std::vector<glm::vec2>& textureCoords,
						const std::vector<unsigned int>& indices,
						const std::vector<std::shared_ptr<Texture>>& textures);
		TexturedMesh(unsigned int usage, const std::vector<Vertex>& vertices,
						const std::vector<unsigned int>& indices,
						const std::vector<std::shared_ptr<Texture>>& textures);

		void init() override;
		void bind() override;
		void draw() override;
		void cleanup() override;

		 std::vector<std::shared_ptr<Texture>> getTextures() override { return textures;}

private:
		const int VERTEX_SIZE = 3;
		const int NORMAL_SIZE = 3;
		const int TEX_COORD_SIZE = 2;

		unsigned int usage;
		std::vector<Vertex> vertexData;
		std::vector<unsigned int> indexData;
		std::vector<std::shared_ptr<Texture>> textures;
		unsigned int vao{};
		VertexBuffer vbo;
		IndexBuffer ebo;
};

class PlainMesh : public virtual Mesh {
 public:
	struct Vertex {
		glm::vec3 position;
	};

	PlainMesh(unsigned int usage, const std::vector<glm::vec3>& vertices,
							 const std::vector<unsigned int>& indices,
							 const std::vector<std::shared_ptr<Texture>>& textures = {});
	PlainMesh(unsigned int usage, const std::vector<Vertex>& vertices,
							 const std::vector<unsigned int>& indices,
							 const std::vector<std::shared_ptr<Texture>>& textures = {});

	void init() override;
	void bind() override;
	void draw() override;
	void cleanup() override;

	std::vector<std::shared_ptr<Texture>> getTextures() override { return textures;}

 private:
	const int VERTEX_SIZE = 3;

	unsigned int usage;
	std::vector<Vertex> vertexData;
	std::vector<unsigned int> indexData;
	std::vector<std::shared_ptr<Texture>> textures;
	unsigned int vao{};
	VertexBuffer vbo;
	IndexBuffer ebo;

};