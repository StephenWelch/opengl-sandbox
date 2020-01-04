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

  directionalLightBuffer.init(GL_STATIC_DRAW, sizeof(DirectionalLightData));
  pointLightBuffer.init(GL_STATIC_DRAW, sizeof(PointLightData));
  spotLightBuffer.init(GL_STREAM_DRAW, sizeof(SpotLightData));

  LOG_INFO("Loading models");
  model.init();

  LOG_INFO("Loading shaders");
  lightingShader.init();

  lightingShader.use();

  directionalLightData.numDirectionalLights = 1;
  pointLightData.numPointLights = 4;
  spotLightData.numSpotLights = 1;
  
  // Lighting config
  directionalLightData.directionalLights[0] = {
    {-0.2f, -1.0f, -0.3f, 0.0f},
    {0.05f, 0.05f, 0.05f, 0.0f},
    {0.4f, 0.4f, 0.4f, 0.0f},
    {0.5f, 0.5f, 0.5f, 0.0f}
  };

  pointLightData.pointLights[0] = {
    {0.7f,  0.2f,  2.0f, 0.0f},
    {0.05f, 0.05f, 0.05f, 0.0f},
    {0.8f, 0.8f, 0.8f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    1.0f,
    0.09,
    0.032
  };

  pointLightData.pointLights[1] = {
    {2.3f, -3.3f, -4.0f, 0.0f},
    {0.05f, 0.05f, 0.05f, 0.0f},
    {0.8f, 0.8f, 0.8f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    1.0f,
    0.09,
    0.032
  };

  pointLightData.pointLights[2] = {
    {-4.0f,  2.0f, -12.0f, 0.0f},
    {0.05f, 0.05f, 0.05f, 0.0f},
    {0.8f, 0.8f, 0.8f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    1.0f,
    0.09,
    0.032
  };

  pointLightData.pointLights[3] = {
    {0.0f,  0.0f, -3.0f, 0.0f},
    {0.05f, 0.05f, 0.05f, 0.0f},
    {0.8f, 0.8f, 0.8f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    1.0f,
    0.09,
    0.032
  };
  
  spotLightData.spotLights[0] = {
    {},
    {},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    1.0f,
    0.09,
    0.032,
    glm::cos(glm::radians(12.5f)),
    glm::cos(glm::radians(15.0f))
  };

  directionalLightBuffer.bindShaderProgram(0);
  lightingShader.setBindingPoint("uDirectionalLights", 0);

  pointLightBuffer.bindShaderProgram(1);
  lightingShader.setBindingPoint("uPointLights", 1);

  spotLightBuffer.bindShaderProgram(2);
  lightingShader.setBindingPoint("uSpotLights", 2);

  directionalLightBuffer.execute([&](auto buffer) {
    buffer->setData(&directionalLightData);
  });
  pointLightBuffer.execute([&](auto buffer) {
    buffer->setData(&pointLightData);
  });
  spotLightBuffer.execute([&](auto buffer) {
    buffer->setData(&spotLightData);
  });

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
    //LOG_DEBUG("uMaterial." + type + "Texture");
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
  spotLightData.spotLights[0].position = glm::vec4(camera->getPosition(), 0.0f);
  spotLightData.spotLights[0].direction = glm::vec4(camera->getTarget(), 0.0f);
  spotLightBuffer.execute([&](auto buffer) {
    buffer->setData(&spotLightData);
  });

  model.bind();
  for (unsigned int i = 0; i < 10; i++)
  {
    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
    float angle = 20.0f * i;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), { 1.0f, 0.3f, 0.5f });
    lightingShader.setMat4("uModel", modelMatrix);
    lightingShader.setMat3("uNormalMatrix", glm::transpose(glm::inverse(modelMatrix)));

    model.draw();
  }

}

void Renderer::close() {
  directionalLightBuffer.cleanup();
  pointLightBuffer.cleanup();
  spotLightBuffer.cleanup();
  lightingShader.cleanup();
  model.cleanup();
}

void Renderer::setWidth(const int& width) { this->width = width; }

void Renderer::setHeight(const int& height) { this->height = height; }