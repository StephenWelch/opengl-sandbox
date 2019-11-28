#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Log.h"
#include "NewShader.h"
#include "util.h"

float modelData[] = {
    // first triangle
    0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

float texCoords[] = {
  0.0f, 0.0f, 
  1.0f, 0.0f, 
  0.5f, 1.0f
};

int indices[]{
    0, 1, 2
};

unsigned int vao;
unsigned int vbo;
unsigned int ebo;

void Renderer::init() {
  Log::getLogger()->info("Initializing Renderer");

  Log::getLogger()->debug("Creating rendering data structures");
  // Generate vertex array and buffers
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  // Bind VAO
  glBindVertexArray(vao);
  {
    // Bind buffer to GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    {
      // Load data into target
      // Static draw denotes that the buffer data will rarely change
      // Dynamic draw would denote that the buffer data changes frequently
      // Stream draw would denote that the buffer data changes every draw
      glBufferData(GL_ARRAY_BUFFER, sizeof(modelData), modelData, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                   GL_STATIC_DRAW);

      // Sets data at location 0 in the VBO to 3 elements, each of which will be
      // an unnormalized float 
      // Stride defines the total size of the attribute,
      // in this case 6*32 bits Offset of 0
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                            (void*)0);
      // Specify an offset of 3 *32 bits for color data
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                            (void*)(3 * sizeof(float)));
      // Enable location 0 in the VBO
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
    }
    // glVertexAttribPointer registered this VBO as the VAO's bound VBO, so we
    // can unbind now
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Do not unbind the EBO while the VAO is still active, because the EBO is
    // stored in the VAO glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);

  Log::getLogger()->debug("Loading shaders");
  shader.init();

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
  Log::getLogger()->info("Finished Renderer initialization");
}

void Renderer::render() {
  float t = glfwGetTime();
  float g = (sin(t) / 2.0f) + 0.5f;

  shader.use();

  shader.setFloat("divider", g);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::close() {
  shader.cleanup();
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}
