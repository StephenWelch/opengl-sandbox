#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <util\MovingAverage.h>
class SimpleTimer {
private:
  bool started = false;
  double lastTime;
  double deltaTime;
  double currentTime;
  MovingAverage movingAverage = MovingAverage(10000);

public:
  double mark();
  double getDelta();
  double getMovingAverage();
};