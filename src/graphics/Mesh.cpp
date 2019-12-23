#include "Mesh.h"
#include <util\Log.h>

Mesh::Mesh(const GLenum& usage, const std::vector<float>& vertices, const std::vector<float>& textureCoords, const std::vector<int>& indices)
{
  this->modelData = std::vector<float>(vertices.size() + textureCoords.size());

  int currentVertex = 0;
  int currentTextureCoord = 0;
  for (int i = 0; i <= modelData.size() - 5; i += VERTEX_ATTRIB_SIZE) {
    this->modelData[i] = vertices[currentVertex];
    this->modelData[i + 1.0] = vertices[currentVertex + 1.0];
    this->modelData[i + 2.0] = vertices[currentVertex + 2.0];
    this->modelData[i + 3.0] = textureCoords[currentTextureCoord];
    this->modelData[i + 4.0] = textureCoords[currentTextureCoord + 1.0];

    currentVertex += 3;
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

  Log::getLogger()->debug("Created VAO with ID: {}", vao);
  Log::getLogger()->debug("Created VBO with ID: {}", vbo);

  glBindVertexArray(vao);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), usage);

      glBufferData(GL_ARRAY_BUFFER, modelData.size() * sizeof(float), modelData.data(), usage);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float),
        (void*)0);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_SIZE * sizeof(float),
        (void*)(3 * sizeof(float)));

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

  
  glBindVertexArray(0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  Log::getLogger()->debug("Finished mesh initialization");
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
