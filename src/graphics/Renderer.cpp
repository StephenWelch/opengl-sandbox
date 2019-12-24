#include <graphics/Renderer.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <util/Log.h>
#include <util/util.h>
#include <graphics/Shader.h>

GLuint vao;
GLuint vbo;
GLuint ebo;

void Renderer::init() {
  Log::getLogger()->info("Initializing Renderer with {}x{} resolution", width, height);

  Log::getLogger()->info("Creating rendering data structures");
  mesh.init();

  Log::getLogger()->info("Loading textures");

  texture.init();

  Log::getLogger()->info("Loading shaders");
  shader.init();

  shader.use();
  shader.setInt("uTexture", 0);
  shader.setMat4("uProjection", camera->getProjectionMatrix());

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)

  Log::getLogger()->info("Finished Renderer initialization");
}

void Renderer::render() {

  texture.bind();

  shader.use();

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = camera->getViewMatrix();
  model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
  
  shader.setMat4("uModel", model);
  shader.setMat4("uView", view);

  mesh.bind();
  mesh.draw();
}

void Renderer::close() {
  shader.cleanup();
  mesh.cleanup();
}

void Renderer::setWidth(const int& width) { this->width = width; }

void Renderer::setHeight(const int& height) { this->height = height; }