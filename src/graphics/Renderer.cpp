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
  cubeMesh.init();

  Log::getLogger()->info("Loading textures");

  texture.init();

  Log::getLogger()->info("Loading shaders");
  cubeShader.init();

  cubeShader.use();
  cubeShader.setInt("uTexture", 0);
  cubeShader.setMat4("uProjection", camera->getProjectionMatrix());

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)

  Log::getLogger()->info("Finished Renderer initialization");
}

void Renderer::render() {

  texture.bind();

  cubeShader.use();

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = camera->getViewMatrix();
  model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
  
  cubeShader.setMat4("uModel", model);
  cubeShader.setMat4("uView", view);

  cubeMesh.bind();
  cubeMesh.draw();
}

void Renderer::close() {
  cubeShader.cleanup();
  cubeMesh.cleanup();
}

void Renderer::setWidth(const int& width) { this->width = width; }

void Renderer::setHeight(const int& height) { this->height = height; }