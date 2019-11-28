#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "NewShader.h"
#include <string>

class Renderer {
 private:
  NewShader shader = NewShader("src/shaders/direct_transform.vert",
                               "src/shaders/single_color.frag");
 public:
  void init();
  void render();
  void close();
};