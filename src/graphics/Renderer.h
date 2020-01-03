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
#include <graphics\Model.h>

#define MAX_DIRECTIONAL_LIGHTS 1
#define MAX_POINT_LIGHTS 4
#define MAX_SPOTLIGHTS 1

class Renderer {
private:

  struct DirectionalLight {
    glm::vec4 direction;

    glm::vec4 ambientIntensity;
    glm::vec4 diffuseIntensity;
    glm::vec4 specularIntensity;
  };

  struct PointLight {
    glm::vec4 position;

    glm::vec4 ambientIntensity;
    glm::vec4 diffuseIntensity;
    glm::vec4 specularIntensity;

    float constant;
    float linear;
    float quadratic;
    float padding;
  };

  struct SpotLight {
    glm::vec4 position;
    glm::vec4 direction;

    glm::vec4 ambientIntensity;
    glm::vec4 diffuseIntensity;
    glm::vec4 specularIntensity;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
    float padding, padding2, padding3;
  };

  struct DirectionalLightData {
    DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
    int numDirectionalLights;
  };

  struct PointLightData{
    PointLight pointLights[MAX_POINT_LIGHTS];
    int numPointLights;
  };

  struct SpotLightData {
    SpotLight spotLights[MAX_SPOTLIGHTS];
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

  // Defined in winding order
  std::vector<glm::vec3> vertices {
    // Back face
    {-0.5f, -0.5f, -0.5f}, // Bottom-left
    {0.5f,  0.5f, -0.5f}, // top-right
    {0.5f, -0.5f, -0.5f}, // bottom-right         
    {0.5f,  0.5f, -0.5f}, // top-right
    {-0.5f, -0.5f, -0.5f}, // bottom-left
    {-0.5f,  0.5f, -0.5f}, // top-left
    // Front face
    {-0.5f, -0.5f,  0.5f}, // bottom-left
    {0.5f, -0.5f,  0.5f}, // bottom-right
    {0.5f,  0.5f,  0.5f}, // top-right
    {0.5f,  0.5f,  0.5f}, // top-right
    {-0.5f,  0.5f,  0.5f}, // top-left
    {-0.5f, -0.5f,  0.5f}, // bottom-left
    // Left face
    {-0.5f,  0.5f,  0.5f}, // top-right
    {-0.5f,  0.5f, -0.5f}, // top-left
    {-0.5f, -0.5f, -0.5f}, // bottom-left
    {-0.5f, -0.5f, -0.5f}, // bottom-left
    {-0.5f, -0.5f,  0.5f}, // bottom-right
    {-0.5f,  0.5f,  0.5f}, // top-right
    // Right face
    {0.5f,  0.5f,  0.5f}, // top-left
    {0.5f, -0.5f, -0.5f}, // bottom-right
    {0.5f,  0.5f, -0.5f}, // top-right         
    {0.5f, -0.5f, -0.5f}, // bottom-right
    {0.5f,  0.5f,  0.5f}, // top-left
    {0.5f, -0.5f,  0.5f}, // bottom-left     
    // Bottom face
    {-0.5f, -0.5f, -0.5f}, // top-right
    {0.5f, -0.5f, -0.5f}, // top-left
    {0.5f, -0.5f,  0.5f}, // bottom-left
    {0.5f, -0.5f,  0.5f}, // bottom-left
    {-0.5f, -0.5f,  0.5f}, // bottom-right
    {-0.5f, -0.5f, -0.5f}, // top-right
    // Top face
    {-0.5f,  0.5f, -0.5f}, // top-left
    {0.5f,  0.5f,  0.5f}, // bottom-right
    {0.5f,  0.5f, -0.5f}, // top-right     
    {0.5f,  0.5f,  0.5f}, // bottom-right
    {-0.5f,  0.5f, -0.5f}, // top-left
    {-0.5f,  0.5f,  0.5f}  // bottom-left
  };

  std::vector<glm::vec3> normals {
      {0.0f,  0.0f, -1.0f},
      {0.0f,  0.0f, -1.0f},
      {0.0f,  0.0f, -1.0f},
      {0.0f,  0.0f, -1.0f},
      {0.0f,  0.0f, -1.0f},
      {0.0f,  0.0f, -1.0f},

      {0.0f,  0.0f, 1.0f},
      {0.0f,  0.0f, 1.0f},
      {0.0f,  0.0f, 1.0f},
      {0.0f,  0.0f, 1.0f},
      {0.0f,  0.0f, 1.0f},
      {0.0f,  0.0f, 1.0f},

      {-1.0f,  0.0f,  0.0f},
      {-1.0f,  0.0f,  0.0f},
      {-1.0f,  0.0f,  0.0f},
      {-1.0f,  0.0f,  0.0f},
      {-1.0f,  0.0f,  0.0f},
      {-1.0f,  0.0f,  0.0f},

      {1.0f,  0.0f,  0.0f},
      {1.0f,  0.0f,  0.0f},
      {1.0f,  0.0f,  0.0f},
      {1.0f,  0.0f,  0.0f},
      {1.0f,  0.0f,  0.0f},
      {1.0f,  0.0f,  0.0f},

      {0.0f, -1.0f,  0.0f},
      {0.0f, -1.0f,  0.0f},
      {0.0f, -1.0f,  0.0f},
      {0.0f, -1.0f,  0.0f},
      {0.0f, -1.0f,  0.0f},
      {0.0f, -1.0f,  0.0f},

      {0.0f,  1.0f,  0.0f},
      {0.0f,  1.0f,  0.0f},
      {0.0f,  1.0f,  0.0f},
      {0.0f,  1.0f,  0.0f},
      {0.0f,  1.0f,  0.0f},
      {0.0f,  1.0f,  0.0f}
  };

  std::vector<glm::vec2> textureCoords {
    // Back face
    {0.0f, 0.0f}, // Bottom-left
    {1.0f, 1.0f}, // top-right
    {1.0f, 0.0f}, // bottom-right         
    {1.0f, 1.0f}, // top-right
    {0.0f, 0.0f}, // bottom-left
    {0.0f, 1.0f}, // top-left
    // Front face
    {0.0f, 0.0f}, // bottom-left
    {1.0f, 0.0f}, // bottom-right
    {1.0f, 1.0f}, // top-right
    {1.0f, 1.0f}, // top-right
    {0.0f, 1.0f}, // top-left
    {0.0f, 0.0f}, // bottom-left
    // Left face
    {1.0f, 0.0f}, // top-right
    {1.0f, 1.0f}, // top-left
    {0.0f, 1.0f}, // bottom-left
    {0.0f, 1.0f}, // bottom-left
    {0.0f, 0.0f}, // bottom-right
    {1.0f, 0.0f}, // top-right
    // Right face
    {1.0f, 0.0f}, // top-left
    {0.0f, 1.0f}, // bottom-right
    {1.0f, 1.0f}, // top-right         
    {0.0f, 1.0f}, // bottom-right
    {1.0f, 0.0f}, // top-left
    {0.0f, 0.0f}, // bottom-left     
    // Bottom face
    {0.0f, 1.0f}, // top-right
    {1.0f, 1.0f}, // top-left
    {1.0f, 0.0f}, // bottom-left
    {1.0f, 0.0f}, // bottom-left
    {0.0f, 0.0f}, // bottom-right
    {0.0f, 1.0f}, // top-right
    // Top face
    {0.0f, 1.0f}, // top-left
    {1.0f, 0.0f}, // bottom-right
    {1.0f, 1.0f}, // top-right     
    {1.0f, 0.0f}, // bottom-right
    {0.0f, 1.0f}, // top-left
    {0.0f, 0.0f}  // bottom-left        
  };

  std::vector<GLuint> indices{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
  };

  Texture2D diffuseTexture = Texture2D(Texture2D::TextureType::DIFFUSE, "res/container2.png", GL_TEXTURE0);
  Texture2D specularTexture = Texture2D(Texture2D::TextureType::SPECULAR, "res/container2_specular.png", GL_TEXTURE1);
  Texture2D emissionTexture = Texture2D(Texture2D::TextureType::EMISSIVE, "res/matrix.jpg", GL_TEXTURE2);
  Mesh cubeMesh = Mesh(GL_STATIC_DRAW, vertices, normals, textureCoords, indices);
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