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

  diffuseTexture.init();
  specularTexture.init();

  Log::getLogger()->info("Loading shaders");
  cubeShader.init();

  cubeShader.use();

  // Lighting config
  cubeShader.setVec3("uLight.ambientIntensity", 0.2f, 0.2f, 0.2f);
  cubeShader.setVec3("uLight.diffuseIntensity", 0.5f, 0.5f, 0.5f); // darken the light a bit to fit the scene
  cubeShader.setVec3("uLight.specularIntensity", 1.0f, 1.0f, 1.0f);

  cubeShader.setVec3("uLight.position", 1.2f, 1.0f, 2.0f);

  cubeShader.setInt("uMaterial.diffuseTexture", diffuseTexture.getTextureUnitNum());
  cubeShader.setInt("uMaterial.specularTexture", specularTexture.getTextureUnitNum());
  cubeShader.setFloat("uMaterial.shininess", 64.0f);

  // Other setup
  cubeShader.setInt("uTexture", 0);
  cubeShader.setMat4("uProjection", camera->getProjectionMatrix());

  Log::getLogger()->info("Finished Renderer initialization");
}

void Renderer::render() {

  diffuseTexture.bind();
  specularTexture.bind();

  cubeShader.use();

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = camera->getViewMatrix();
  //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
  
  cubeShader.setMat3("uNormalMatrix", glm::transpose(glm::inverse(model)));
  cubeShader.setVec3("uViewPos", camera->getPosition());
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