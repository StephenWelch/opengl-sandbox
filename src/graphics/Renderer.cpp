#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../util/Log.h"
#include "Shader.h"
#include "../util/util.h"
#include <stb_image.h>

float modelData[] = {
    // positions // colors // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

int indices[]{
    3, 0, 1,
    3, 2, 1
};

GLuint vao;
GLuint vbo;
GLuint ebo;
GLuint textureA, textureB;

void Renderer::init() {
  Log::getLogger()->info("Initializing Renderer");

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
      glBufferData(GL_ARRAY_BUFFER, sizeof(modelData), modelData, GL_STATIC_DRAW);

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
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
  stbi_set_flip_vertically_on_load(true);

  
  glGenTextures(1, &textureA);
  glBindTexture(GL_TEXTURE_2D, textureA);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  std::string textureAPath = "res/container.jpg";
  int widthA, heightA, nrChannelsA;
  unsigned char *dataA =
      stbi_load(textureAPath.c_str(), &widthA, &heightA, &nrChannelsA, 0);
  if (dataA) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthA, heightA, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, dataA);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    Log::getLogger()->error("Failed to load texture {}", textureAPath);
  }
  stbi_image_free(dataA);

  glGenTextures(1, &textureB);
  glBindTexture(GL_TEXTURE_2D, textureB);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  std::string textureBPath = "res/awesomeface.png";
  int widthB, heightB, nrChannelsB;
  unsigned char *dataB =
      stbi_load(textureBPath.c_str(), &widthB, &heightB, &nrChannelsB, 0);
  if (dataB) {
    // RGBA because this texture is a PNG, which supports transparency
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthB, heightB, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, dataB);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    Log::getLogger()->error("Failed to load texture {}", textureBPath);
  }
  stbi_image_free(dataB);

  Log::getLogger()->info("Loading shaders");
  shader.init();

  // Configure which uniform belongs to each texture unit
  shader.use();
  shader.setInt("ourTextureA", 0);
  shader.setInt("ourTextureB", 1);

  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
  Log::getLogger()->info("Finished Renderer initialization");
}

void Renderer::render() {

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureA);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textureB);

  shader.use();

  float t = float(glfwGetTime());
  shader.setFloat("divider", (sin(t) / 2.0f) + 0.5f);
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
  shader.setMat4("transform", trans);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::close() {
  shader.cleanup();
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}
