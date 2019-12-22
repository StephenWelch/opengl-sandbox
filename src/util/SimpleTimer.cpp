#include <util/SimpleTimer.h>

double SimpleTimer::mark() {
  currentTime = glfwGetTime();
  if (!started) {
    started = true;
    lastTime = currentTime;
    deltaTime = currentTime - lastTime;
    return deltaTime;
  }
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
  accumulator = (MOVING_AVERAGE_ALPHA * deltaTime) + (1.0 - MOVING_AVERAGE_ALPHA) * accumulator;
  return deltaTime;
}

double SimpleTimer::getDelta() {
  return deltaTime;
}

double SimpleTimer::getMovingAverage()
{
  return accumulator;
}

