#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class SimpleTimer {
private:
  const double MOVING_AVERAGE_ALPHA = 0.03;
  bool started = false;
  double lastTime;
  double deltaTime;
  double currentTime;
  double accumulator;

public:
  double mark();
  double getDelta();
  double getMovingAverage();
};