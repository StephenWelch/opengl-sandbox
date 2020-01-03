#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <memory>
#include <graphics/Texture2D.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>
#include <graphics/Mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <graphics/Model.h>
#include <graphics/Light.h>
#include <util/util.h>
#include <graphics/Buffer.h>

#define MAX_DIRECTIONAL_LIGHTS 100
#define MAX_POINT_LIGHTS 100
#define MAX_SPOTLIGHTS 100

class Renderer {
private:

  struct DirectionalLightData {
    DirectionalLight::Data directionalLights[MAX_DIRECTIONAL_LIGHTS];
    int numDirectionalLights;
  };

  struct PointLightData{
    PointLight::Data pointLights[MAX_POINT_LIGHTS];
    int numPointLights;
  };

  struct SpotLightData {
    SpotLight::Data spotLights[MAX_SPOTLIGHTS];
    int numSpotLights;
  };

  DirectionalLightData directionalLightData;
  PointLightData pointLightData;
  SpotLightData spotLightData;
  UniformBuffer directionalLightBuffer = UniformBuffer(GL_STATIC_DRAW, sizeof(DirectionalLightData));
  UniformBuffer pointLightBuffer = UniformBuffer(GL_STATIC_DRAW, sizeof(PointLightData));
  UniformBuffer spotLightBuffer = UniformBuffer(GL_STREAM_DRAW, sizeof(SpotLightData));

  const std::unique_ptr<Camera>& camera;

  int width;
  int height;
  Shader lightingShader = Shader("shaders/lightmap_textured_model.vert",
    "shaders/lightmap_textured_model.frag");

  // positions all containers
  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f,  0.0f,  0.0f),
      glm::vec3(2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f,  2.0f, -2.5f),
      glm::vec3(1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
  };

  Texture2D diffuseTexture = Texture2D(Texture2D::TextureType::DIFFUSE, "res/container2.png", GL_TEXTURE0);
  Texture2D specularTexture = Texture2D(Texture2D::TextureType::SPECULAR, "res/container2_specular.png", GL_TEXTURE1);
  Texture2D emissionTexture = Texture2D(Texture2D::TextureType::EMISSIVE, "res/matrix.jpg", GL_TEXTURE2);
  Mesh cubeMesh = util::generateCube(1.0f, GL_STATIC_DRAW);
  Model model = Model(cubeMesh, { diffuseTexture, specularTexture, emissionTexture });

public:
  Renderer(const std::unique_ptr<Camera>& camera, const int& width, const int& height)
    : camera(camera), width(width), height(height) {};
  void init();
  void render();
  void close();
  void setWidth(const int& width);
  void setHeight(const int& height);
};