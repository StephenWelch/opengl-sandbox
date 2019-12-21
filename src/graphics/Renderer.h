#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include "Shader.h"
#include "Texture2D.h"

class Renderer {
private:
  int width;
  int height;

  Shader shader = Shader("src/shaders/direct_transform.vert",
    "src/shaders/single_color.frag");
  Texture2D textureA = Texture2D("res/container.jpg", GL_TEXTURE0);
  Texture2D textureB = Texture2D("res/awesomeface.png", GL_TEXTURE1);

public:
  Renderer(const int& width, const int& height)
    : width(width), height(height) {};
  void init();
  void render();
  void close();
  void setWidth(const int& width);
  void setHeight(const int& height);
};