#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Renderer.h>
#include <graphics/Shader.h>
#include <stb_image.h>
#include <util/Log.h>
#include <util/util.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint vao;
GLuint vbo;
GLuint ebo;

void Renderer::init() {
  LOG_INFO("Initializing Renderer with {}x{} resolution", width, height);

  LOG_INFO("Loading models");
  model.init();

  LOG_INFO("Loading shaders");
  lightingShader.init();

  lightingShader.use();

  directionalLightManager.init();
  pointLightManager.init();
  spotLightManager.init();

  directionalLightManager.setBindingPoint(0);
  lightingShader.setBindingPoint("uDirectionalLights", 0);
  pointLightManager.setBindingPoint(1);
  lightingShader.setBindingPoint("uPointLights", 1);
  spotLightManager.setBindingPoint(2);
  lightingShader.setBindingPoint("uSpotLights", 2);

  directionalLightManager.addLight(dirLight);
  pointLightManager.addLight(pointLight1);
  pointLightManager.addLight(pointLight2);
  pointLightManager.addLight(pointLight3);
  pointLightManager.addLight(pointLight4);
  spotLightManager.addLight(spotLight);

  directionalLightManager.updateAll();
  pointLightManager.updateAll();
  spotLightManager.updateAll();

  for (const Texture2D& texture : model.getTextures()) {
    std::string type;
    switch (texture.getType()) {
      case Texture2D::TextureType::SPECULAR:
        type = "specular";
        break;
      case Texture2D::TextureType::DIFFUSE:
        type = "diffuse";
        break;
      case Texture2D::TextureType::EMISSIVE:
        type = "emissive";
        break;
    }
    // LOG_DEBUG("uMaterial." + type + "Texture");
    lightingShader.setInt("uMaterial." + type + "Texture",
                          texture.getTextureUnitNum());
  }

  lightingShader.setBool("uEmissionsEnabled", false);
  lightingShader.setFloat("uMaterial.shininess", 64.0f);

  // Other setup
  lightingShader.setMat4("uProjection", camera->getProjectionMatrix());

  LOG_INFO("Finished Renderer initialization");
}

void Renderer::render() {
  lightingShader.use();

  glm::mat4 viewMatrix = camera->getViewMatrix();
  lightingShader.setMat4("uView", viewMatrix);
  lightingShader.setVec3("uViewPos", camera->getPosition());

  // User
  spotLight->position = glm::vec4(camera->getPosition(), 0.0f);
  spotLight->direction = glm::vec4(camera->getTarget(), 0.0f);
  spotLightManager.updateAll();

  model.bind();
  for (unsigned int i = 0; i < 10; i++) {
    // calculate the model matrix for each object and pass it to shader before
    // drawing
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
    float angle = 20.0f * (i + 1);
    modelMatrix =
        glm::rotate(modelMatrix, glm::radians((float)glfwGetTime() * angle),
                    {1.0f, 0.3f, 0.5f});
    lightingShader.setMat4("uModel", modelMatrix);
    lightingShader.setMat3("uNormalMatrix",
                           glm::transpose(glm::inverse(modelMatrix)));

    model.draw();
  }
}

void Renderer::close() {
  /*directionalLightBuffer.cleanup();
  pointLightBuffer.cleanup();
  spotLightBuffer.cleanup();*/
  lightingShader.cleanup();
  model.cleanup();
}

void Renderer::setWidth(const int& width) { this->width = width; }

void Renderer::setHeight(const int& height) { this->height = height; }