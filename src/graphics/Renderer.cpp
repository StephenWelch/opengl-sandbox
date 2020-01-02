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
  LOG_INFO("Initializing Renderer with {}x{} resolution", width, height);

  LOG_INFO("Loading models");
  model.init();

  LOG_INFO("Loading shaders");
  lightingShader.init();

  lightingShader.use();

  // Lighting config
  lightingShader.setVec3("uDirectionalLights[0].direction", -0.2f, -1.0f, -0.3f);
  lightingShader.setVec3("uDirectionalLights[0].ambientIntensity", 0.05f, 0.05f, 0.05f);
  lightingShader.setVec3("uDirectionalLights[0].diffuseIntensity", 0.4f, 0.4f, 0.4f);
  lightingShader.setVec3("uDirectionalLights[0].specularIntensity", 0.5f, 0.5f, 0.5f);
  // point light 1
  lightingShader.setVec3("uPointLights[0].position", pointLightPositions[0]);
  lightingShader.setVec3("uPointLights[0].ambientIntensity", 0.05f, 0.05f, 0.05f);
  lightingShader.setVec3("uPointLights[0].diffuseIntensity", 0.8f, 0.8f, 0.8f);
  lightingShader.setVec3("uPointLights[0].specularIntensity", 1.0f, 1.0f, 1.0f);
  lightingShader.setFloat("uPointLights[0].constant", 1.0f);
  lightingShader.setFloat("uPointLights[0].linear", 0.09);
  lightingShader.setFloat("uPointLights[0].quadratic", 0.032);
  // point light 2
  lightingShader.setVec3("uPointLights[1].position", pointLightPositions[1]);
  lightingShader.setVec3("uPointLights[1].ambientIntensity", 0.05f, 0.05f, 0.05f);
  lightingShader.setVec3("uPointLights[1].diffuseIntensity", 0.8f, 0.8f, 0.8f);
  lightingShader.setVec3("uPointLights[1].specularIntensity", 1.0f, 1.0f, 1.0f);
  lightingShader.setFloat("uPointLights[1].constant", 1.0f);
  lightingShader.setFloat("uPointLights[1].linear", 0.09);
  lightingShader.setFloat("uPointLights[1].quadratic", 0.032);
  // point light 3
  lightingShader.setVec3("uPointLights[2].position", pointLightPositions[2]);
  lightingShader.setVec3("uPointLights[2].ambientIntensity", 0.05f, 0.05f, 0.05f);
  lightingShader.setVec3("uPointLights[2].diffuseIntensity", 0.8f, 0.8f, 0.8f);
  lightingShader.setVec3("uPointLights[2].specularIntensity", 1.0f, 1.0f, 1.0f);
  lightingShader.setFloat("uPointLights[2].constant", 1.0f);
  lightingShader.setFloat("uPointLights[2].linear", 0.09);
  lightingShader.setFloat("uPointLights[2].quadratic", 0.032);
  // point light 4
  lightingShader.setVec3("uPointLights[3].position", pointLightPositions[3]);
  lightingShader.setVec3("uPointLights[3].ambientIntensity", 0.05f, 0.05f, 0.05f);
  lightingShader.setVec3("uPointLights[3].diffuseIntensity", 0.8f, 0.8f, 0.8f);
  lightingShader.setVec3("uPointLights[3].specularIntensity", 1.0f, 1.0f, 1.0f);
  lightingShader.setFloat("uPointLights[3].constant", 1.0f);
  lightingShader.setFloat("uPointLights[3].linear", 0.09);
  lightingShader.setFloat("uPointLights[3].quadratic", 0.032);
  // uSpotLights[0]
  lightingShader.setVec3("uSpotLights[0].ambientIntensity", 0.0f, 0.0f, 0.0f);
  lightingShader.setVec3("uSpotLights[0].diffuseIntensity", 1.0f, 1.0f, 1.0f);
  lightingShader.setVec3("uSpotLights[0].specularIntensity", 1.0f, 1.0f, 1.0f);
  lightingShader.setFloat("uSpotLights[0].constant", 1.0f);
  lightingShader.setFloat("uSpotLights[0].linear", 0.09);
  lightingShader.setFloat("uSpotLights[0].quadratic", 0.032);
  lightingShader.setFloat("uSpotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
  lightingShader.setFloat("uSpotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)));
  
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
    LOG_DEBUG("uMaterial." + type + "Texture");
    lightingShader.setInt("uMaterial." + type + "Texture", texture.getTextureUnitNum());
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
  lightingShader.setVec3("uSpotLights[0].position", camera->getPosition());
  lightingShader.setVec3("uSpotLights[0].direction", camera->getTarget());


  model.bind();
  for (unsigned int i = 0; i < 10; i++)
  {
    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
    float angle = 20.0f * i;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    lightingShader.setMat4("uModel", modelMatrix);
    lightingShader.setMat3("uNormalMatrix", glm::transpose(glm::inverse(modelMatrix)));

    model.draw();
  }

}

void Renderer::close() {
  lightingShader.cleanup();
  model.cleanup();
}

void Renderer::setWidth(const int& width) { this->width = width; }

void Renderer::setHeight(const int& height) { this->height = height; }