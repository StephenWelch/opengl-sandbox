#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <memory>
#include <graphics/Texture2D.h>
#include <graphics/Camera.h>
#include <graphics/Shader.h>
#include <graphics/Mesh.h>

class Renderer {
private:
  int width;
  int height;

  const std::unique_ptr<Camera>& camera;

  Shader cubeShader = Shader("shaders/lightmap_textured_model.vert",
    "shaders/lightmap_textured_model.frag");
  Texture2D diffuseTexture = Texture2D("res/container2.png", GL_TEXTURE0);
  Texture2D specularTexture = Texture2D("res/container2_specular.png", GL_TEXTURE1);

  std::vector<float> vertices {
      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,

      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
  };

  std::vector<float> normals{
      0.0f,  0.0f, -1.0f,
      0.0f,  0.0f, -1.0f,
      0.0f,  0.0f, -1.0f,
      0.0f,  0.0f, -1.0f,
      0.0f,  0.0f, -1.0f,
      0.0f,  0.0f, -1.0f,

      0.0f,  0.0f, 1.0f,
      0.0f,  0.0f, 1.0f,
      0.0f,  0.0f, 1.0f,
      0.0f,  0.0f, 1.0f,
      0.0f,  0.0f, 1.0f,
      0.0f,  0.0f, 1.0f,

      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,

      1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.0f,

      0.0f, -1.0f,  0.0f,
      0.0f, -1.0f,  0.0f,
      0.0f, -1.0f,  0.0f,
      0.0f, -1.0f,  0.0f,
      0.0f, -1.0f,  0.0f,
      0.0f, -1.0f,  0.0f,

      0.0f,  1.0f,  0.0f,
      0.0f,  1.0f,  0.0f,
      0.0f,  1.0f,  0.0f,
      0.0f,  1.0f,  0.0f,
      0.0f,  1.0f,  0.0f,
      0.0f,  1.0f,  0.0f,
  };

  std::vector<float> textureCoords{
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,

      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,

      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 0.0f,

      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 0.0f,

      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,

      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f
  };

  std::vector<int> indices{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
  };

  Mesh cubeMesh = Mesh(GL_STATIC_DRAW, vertices, normals, textureCoords, indices);

public:
  Renderer(const std::unique_ptr<Camera>& camera, const int& width, const int& height)
    : camera(camera), width(width), height(height) {};
  void init();
  void render();
  void close();
  void setWidth(const int& width);
  void setHeight(const int& height);
};