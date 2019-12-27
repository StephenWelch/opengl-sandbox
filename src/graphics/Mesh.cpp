#include "Mesh.h"
#include <util\Log.h>

Mesh::Mesh(const GLenum& usage, const std::vector<float>& vertices, const std::vector<float> normals, const std::vector<float>& textureCoords, const std::vector<int>& indices)
{
  this->vertexData = vertices;
  this->normalData = normals;
  this->texCoordData = textureCoords;
  this->indexData = indices;
  this->usage = usage;

  LOG_DEBUG("Created mesh with {} vertices",  vertexData.size());
}

void Mesh::init()
{
  LOG_DEBUG("Initializing mesh");
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), usage);

      int vertexDataSize = vertexData.size() * sizeof(float);
      int normalDataSize = normalData.size() * sizeof(float);
      int texCoordDataSize = texCoordData.size() * sizeof(float);

      glBufferData(GL_ARRAY_BUFFER, vertexDataSize + normalDataSize + texCoordDataSize, nullptr, usage);
      glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, vertexData.data());
      glBufferSubData(GL_ARRAY_BUFFER, vertexDataSize, normalDataSize, normalData.data());
      glBufferSubData(GL_ARRAY_BUFFER, vertexDataSize + normalDataSize, texCoordDataSize, texCoordData.data());

      glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
        (void*)0);
      glVertexAttribPointer(1, NORMAL_SIZE, GL_FLOAT, GL_FALSE, NORMAL_SIZE * sizeof(float),
        (void*)(vertexDataSize));
      glVertexAttribPointer(2, TEX_COORD_SIZE, GL_FLOAT, GL_FALSE, TEX_COORD_SIZE * sizeof(float),
        (void*)(vertexDataSize + normalDataSize));

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
