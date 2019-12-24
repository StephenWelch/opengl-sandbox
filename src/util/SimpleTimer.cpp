#include <util/SimpleTimer.h>

double SimpleTimer::mark() {
  currentTime = glfwGetTime();
  if (!started) {
    started = true;
    lastTime = currentTime;
    deltaTime = currentTime - lastTime;
    return movingAverage.update(deltaTime);
  }
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
  return movingAverage.update(deltaTime);
}

double SimpleTimer::getDelta() {
  return deltaTime;
}

double SimpleTimer::getMovingAverage()
{
  return movingAverage.getAverage();
}

