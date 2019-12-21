#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../util/Log.h"
#include "../util/util.h"
#include "Shader.h"

float modelData[] = {
    // positions // colors // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

int indices[]{3, 0, 1, 3, 2, 1};

GLuint vao;
GLuint vbo;
GLuint ebo;

void Renderer::init() {
  Log::getLogger()->info("Initializing Renderer with {}x{} resolution", width, height);

  Log::getLogger()->info("Creating rendering data structures");
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
      glBufferData(GL_ARRAY_BUFFER, sizeof(modelData), modelData,
                   GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                   GL_STATIC_DRAW);

      // Sets data at location 0 in the VBO to 3 elements, each of which will be
      // an unnormalized float
      // Stride defines the total size of the attribute,
      // in this case 9*32 bits Offset of 0
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                            (void*)0);
      // Specify an offset of 3 *32 bits for color data
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                            (void*)(3 * sizeof(float)));
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                            (void*)(6 * sizeof(float)));
      // Enable location 0 in the VBO
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
    }
    // glVertexAttribPointer registered this VBO as the VAO's bound VBO, so we
    // can unbind now
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Do not unbind the EBO while the VAO is still active, because the EBO is
    // stored in the VAO glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);

  Log::getLogger()->info("Loading textures");

  textureA.init();
  textureB.init();

  Log::getLogger()->info("Loading shaders");
  shader.init();

  // Configure which uniform belongs to each texture unit
  shader.use();
  shader.setInt("textureA", 0);
  shader.setInt("textureB", 1);

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
  Log::getLogger()->info("Finished Renderer initialization");
}

void Renderer::render() {
  textureA.bind();
  textureB.bind();

  shader.use();

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  projection =
      glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
  shader.setMat4("model", model);
  shader.setMat4("view", view);
  // note: currently we set the projection matrix each frame, but since the
  // projection matrix rarely changes it's often best practice to set it outside
  // the main loop only once.
  shader.setMat4("projection", projection);

  float t = float(glfwGetTime());
  shader.setFloat("divider", (sin(t) / 2.0f) + 0.5f);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::close() {
  shader.cleanup();
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}

void Renderer::setWidth(const int& width) { this->width = width; }

void Renderer::setHeight(const int& height) { this->height = height; }
