#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Buffer.h>
#include <graphics/Camera.h>
#include <graphics/Light.h>
#include <graphics/Mesh.h>
#include <graphics/Model.h>
#include <graphics/Shader.h>
#include <graphics/Texture2D.h>
#include <util/util.h>

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>

class Renderer {
 private:
  DirectionalLightManager directionalLightManager;
  PointLightManager pointLightManager;
  SpotLightManager spotLightManager;

  const std::unique_ptr<Camera>& camera;

  int width;
  int height;
  Shader lightingShader = Shader("shaders/lightmap_textured_model.vert",
                                 "shaders/lightmap_textured_model.frag");

  // positions all containers
  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  std::shared_ptr<DirectionalLight> dirLight =
      std::make_shared<DirectionalLight>(
          glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f),
          glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));

  std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(
      glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f),
      glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
      0.032);

  std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(
      glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(0.05f, 0.05f, 0.05f),
      glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
      0.032);

  std::shared_ptr<PointLight> pointLight3 = std::make_shared<PointLight>(
      glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.05f, 0.05f, 0.05f),
      glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
      0.032);

  std::shared_ptr<PointLight> pointLight4 = std::make_shared<PointLight>(
      glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.05f, 0.05f, 0.05f),
      glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
      0.032);

  std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>(
      glm::vec3(), glm::vec3(), glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
      0.032, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));

  Texture2D diffuseTexture = Texture2D(Texture2D::TextureType::DIFFUSE,
                                       "res/container2.png", GL_TEXTURE0);
  Texture2D specularTexture =
      Texture2D(Texture2D::TextureType::SPECULAR, "res/container2_specular.png",
                GL_TEXTURE1);
  Texture2D emissionTexture = Texture2D(Texture2D::TextureType::EMISSIVE,
                                        "res/matrix.jpg", GL_TEXTURE2);
  Mesh cubeMesh = util::generateCube(1.0f, GL_STATIC_DRAW);
  Model model =
      Model(cubeMesh, {diffuseTexture, specularTexture, emissionTexture});

 public:
  Renderer(const std::unique_ptr<Camera>& camera, const int& width,
           const int& height)
      : camera(camera), width(width), height(height){};
  void init();
  void render();
  void close();
  void setWidth(const int& width);
  void setHeight(const int& height);
};