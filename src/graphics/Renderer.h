#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Shader.h"
#include <string>

class Renderer {
 private:
  Shader shader = Shader("src/shaders/direct_transform.vert",
                               "src/shaders/single_color.frag");
 public:
  void init();
  void render();
  void close();
};