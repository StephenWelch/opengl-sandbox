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

  Shader shader = Shader("shaders/textured_model.vert",
    "shaders/textured_model.frag");
  Texture2D textureA = Texture2D("res/container.jpg", GL_TEXTURE0);
  Texture2D textureB = Texture2D("res/awesomeface.png", GL_TEXTURE1);
  
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
  
  std::vector<float> textureCoords {
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
  
  std::vector<int> indices {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
  };
  
  Mesh mesh = Mesh(GL_STATIC_DRAW, vertices, textureCoords, indices);

public:
  Renderer(const std::unique_ptr<Camera>& camera, const int& width, const int& height)
    : camera(camera), width(width), height(height) {};
  void init();
  void render();
  void close();
  void setWidth(const int& width);
  void setHeight(const int& height);
};