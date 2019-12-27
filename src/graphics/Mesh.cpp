#include "Mesh.h"
#include <util\Log.h>

Mesh::Mesh(const GLenum& usage, const std::vector<float>& vertices, const std::vector<float> normals, const std::vector<float>& textureCoords, const std::vector<int>& indices)
{
  this->modelData = std::vector<float>();

  int numElements = vertices.size() + normals.size() + textureCoords.size();
  int currentVertex = 0;
  int currentNormal = 0;
  int currentTextureCoord = 0;

  while(modelData.size() < numElements) {
    // Pack vertices
    this->modelData.push_back(vertices[currentVertex]);
    this->modelData.push_back(vertices[currentVertex + 1.0]);
    this->modelData.push_back(vertices[currentVertex + 2.0]);
    // Pack normals
    this->modelData.push_back(normals[currentNormal]);
    this->modelData.push_back(normals[currentNormal + 1.0]);
    this->modelData.push_back(normals[currentNormal + 2.0]);
    // Pack texture coordinates
    this->modelData.push_back(textureCoords[currentTextureCoord]);
    this->modelData.push_back(textureCoords[currentTextureCoord + 1.0]);

    currentVertex += 3;
    currentNormal += 3;
    currentTextureCoord += 2;
  }
  this->indexData = indices;
  this->usage = usage;

  Log::getLogger()->debug("Created mesh with {} vertices and data size of {}", modelData.size() / VERTEX_ATTRIB_SIZE,  modelData.size());
}

void Mesh::init()
{
  Log::getLogger()->debug("Initializing mesh");
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), usage);

      glBufferData(GL_ARRAY_BUFFER, modelData.size() * sizeof(float), modelData.data(), usage);
      glVertexAttribPointer(0, VERTEX_SIZE, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float),
        (void*)0);
      glVertexAttribPointer(1, NORMAL_SIZE, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float),
        (void*)((VERTEX_SIZE) * sizeof(float)));
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float),
        (void*)((VERTEX_SIZE + NORMAL_SIZE) * sizeof(float)));

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

  
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  Log::getLogger()->debug("Initialized mesh with VAO: {}\tVBO: {}\tEBO: {}", vao, vbo, ebo);
}

void Mesh::bind()
{
  //Log::getLogger()->debug("Binding VAO with ID: {}", vao);
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
