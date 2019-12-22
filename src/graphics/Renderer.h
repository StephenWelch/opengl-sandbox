#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <memory>
#include <graphics/Texture2D.h>
#include <graphics/Camera.h>
#include <graphics\Shader.h>

class Renderer {
private:
  int width;
  int height;

  const std::unique_ptr<Camera>& camera;

  Shader shader = Shader("shaders/direct_transform.vert",
    "shaders/single_color.frag");
  Texture2D textureA = Texture2D("res/container.jpg", GL_TEXTURE0);
  Texture2D textureB = Texture2D("res/awesomeface.png", GL_TEXTURE1);

public:
  Renderer(const std::unique_ptr<Camera>& camera, const int& width, const int& height)
    : camera(camera), width(width), height(height) {};
  void init();
  void render();
  void close();
  void setWidth(const int& width);
  void setHeight(const int& height);
};