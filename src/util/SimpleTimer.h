#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class SimpleTimer {
private:
  bool started = false;
  double lastTime;
  double deltaTime;
  double currentTime;

public:
  double mark();
  double getDelta();
};