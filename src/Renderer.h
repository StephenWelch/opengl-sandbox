#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Shader.h"
#include "ShaderProgram.h"
#include <string>

class Renderer {
 private:
  ShaderProgram shaderProgram;

 public:
  void init();
  void render();
  void close();
};