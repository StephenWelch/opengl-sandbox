#include "Mesh.h"

#include <util\Log.h>

TexturedMesh::TexturedMesh(unsigned int usage, const std::vector<glm::vec3>& vertices,
				const std::vector<glm::vec3>& normals,
				const std::vector<glm::vec2>& textureCoords,
				const std::vector<unsigned int>& indices,
				const std::vector<std::shared_ptr<Texture>>& textures)
{
		this->usage = usage;
		for (int i = 0; i<vertices.size(); i++) {
				vertexData.push_back(Vertex{vertices[i], normals[i], textureCoords[i]});
		}
		this->indexData = indices;
		this->textures = textures;
}

TexturedMesh::TexturedMesh(unsigned int usage, const std::vector<Vertex>& vertices,
				const std::vector<unsigned int>& indices,
				const std::vector<std::shared_ptr<Texture>>& textures)
{
		this->usage = usage;
		this->vertexData = vertices;
		this->indexData = indices;
		this->textures = textures;

		LOG_DEBUG("Created mesh with {} vertices", vertexData.size());
}

void TexturedMesh::init()
{
		LOG_DEBUG("Initializing mesh");
		
		vbo.init(usage, vertexData.size()*sizeof(Vertex));
		ebo.init(usage, indexData.size()*sizeof(int));
		vbo.setData(vertexData.data());
		ebo.setData(indexData.data());

		glCreateVertexArrays(1, &vao);

		glVertexArrayVertexBuffer(vao, 0, vbo.getId(), 0, sizeof(Vertex));
		glVertexArrayElementBuffer(vao, ebo.getId());
		
		glEnableVertexArrayAttrib(vao, 0);
		glEnableVertexArrayAttrib(vao, 1);
		glEnableVertexArrayAttrib(vao, 2);

	glVertexArrayAttribFormat(vao, 0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexArrayAttribFormat(vao, 1, NORMAL_SIZE, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
	glVertexArrayAttribFormat(vao, 2, TEX_COORD_SIZE, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoords));


	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribBinding(vao, 2, 0);

	for(auto& texture : textures) {
			texture->init();
	}

	LOG_DEBUG("Initialized mesh with VAO: {}\tVBO: {}\tEBO: {}", vao, vbo.getId(),
					ebo.getId());
}

void TexturedMesh::bind()
{
		// LOG_DEBUG("Binding VAO with ID: {}", vao);
		for(auto& texture : textures) {
				texture->bind();
		}
		glBindVertexArray(vao);
}

void TexturedMesh::draw()
{
		glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, nullptr);
		// glDrawArrays(GL_TRIANGLES, 0, modelData.size() / VERTEX_ATTRIB_SIZE);
}

void TexturedMesh::cleanup()
{
		glDeleteVertexArrays(1, &vao);
		vbo.cleanup();
		ebo.cleanup();
}

PlainMesh::PlainMesh(unsigned int usage, const std::vector<glm::vec3>& vertices,
										 const std::vector<unsigned int>& indices,
										 const std::vector<std::shared_ptr<Texture>>& textures)
{
	this->usage = usage;
	for (auto vertex : vertices) {
		vertexData.push_back(Vertex{vertex});
	}
	this->indexData = indices;
	this->textures = textures;
}

PlainMesh::PlainMesh(unsigned int usage, const std::vector<Vertex>& vertices,
										 const std::vector<unsigned int>& indices,
										 const std::vector<std::shared_ptr<Texture>>& textures)
{
	this->usage = usage;
	this->vertexData = vertices;
	this->indexData = indices;
	this->textures = textures;

	LOG_DEBUG("Created mesh with {} vertices", vertexData.size());
}

void PlainMesh::init()
{
	LOG_DEBUG("Initializing mesh");

	vbo.init(usage, vertexData.size()*sizeof(Vertex));
	ebo.init(usage, indexData.size()*sizeof(unsigned int));
	vbo.setData(vertexData.data());
	ebo.setData(indexData.data());

	glCreateVertexArrays(1, &vao);

	glVertexArrayVertexBuffer(vao, 0, vbo.getId(), 0, sizeof(Vertex));
	glVertexArrayElementBuffer(vao, ebo.getId());

	glEnableVertexArrayAttrib(vao, 0);

	glVertexArrayAttribFormat(vao, 0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));

	glVertexArrayAttribBinding(vao, 0, 0);

	for(auto& texture : textures) {
		texture->init();
	}

	LOG_DEBUG("Initialized mesh with VAO: {}\tVBO: {}\tEBO: {}", vao, vbo.getId(),
						ebo.getId());
}

void PlainMesh::bind()
{
	// LOG_DEBUG("Binding VAO with ID: {}", vao);

	for(auto& texture : textures) {
		texture->bind();
	}
	glBindVertexArray(vao);
}

void PlainMesh::draw()
{
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, nullptr);
//	 glDrawArrays(GL_TRIANGLES, 0, 36);
}

void PlainMesh::cleanup()
{
	glDeleteVertexArrays(1, &vao);
	vbo.cleanup();
	ebo.cleanup();
}
