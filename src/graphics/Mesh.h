#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Buffer.h>
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"

class Mesh {
public:
		struct Vertex {
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texCoords;
		};

		Mesh(const unsigned int& usage, const std::vector<glm::vec3>& vertices,
						const std::vector<glm::vec3>& normals,
						const std::vector<glm::vec2>& textureCoords,
						const std::vector<unsigned int>& indices,
						const std::vector<Texture>& textures);
		Mesh(const unsigned int& usage, const std::vector<Vertex>& vertices,
						const std::vector<unsigned int>& indices,
						const std::vector<Texture>& textures);

		void init();
		void bind();
		void draw();
		void cleanup();
		auto getTextures() const {return textures; }
private:
		const int VERTEX_SIZE = 3;
		const int NORMAL_SIZE = 3;
		const int TEX_COORD_SIZE = 2;

		unsigned int usage;
		std::vector<Vertex> vertexData;
		std::vector<unsigned int> indexData;
		std::vector<Texture> textures;
		unsigned int vao{};
		VertexBuffer vbo;
		IndexBuffer ebo;
};