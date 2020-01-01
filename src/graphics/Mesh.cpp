#include "Mesh.h"
#include <util\Log.h>

Mesh::Mesh(const GLenum& usage, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3> normals, const std::vector<glm::vec2>& textureCoords, const std::vector<GLuint>& indices)
{
  this->usage = usage;
  for (int i = 0; i < vertices.size(); i++) {
    vertexData.push_back(Vertex{ vertices[i], normals[i], textureCoords[i] });
  }
  this->indexData = indices;
}

Mesh::Mesh(const GLenum& usage, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
  this->usage = usage;
  this->vertexData = vertices;
  this->indexData = indices;

  LOG_DEBUG("Created mesh with {} vertices", vertexData.size());
}

void Mesh::init()
{
  LOG_DEBUG("Initializing mesh");
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), usage);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), vertexData.data(), usage);

  glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    (void*)offsetof(Vertex, position));
  glVertexAttribPointer(1, NORMAL_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    (void*)offsetof(Vertex, normal));
  glVertexAttribPointer(2, TEX_COORD_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex),
    (void*)offsetof(Vertex, texCoords));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
    
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  LOG_DEBUG("Initialized mesh with VAO: {}\tVBO: {}\tEBO: {}", vao, vbo, ebo);
}

void Mesh::bind()
{
  //LOG_DEBUG("Binding VAO with ID: {}", vao);
  glBindVertexArray(vao);
}

void Mesh::draw()
{
  glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, modelData.size() / VERTEX_ATTRIB_SIZE);
}

void Mesh::cleanup()
{
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}
