#include <util/SimpleTimer.h>

double SimpleTimer::mark() {
  currentTime = glfwGetTime();
  if (!started) {
    started = true;
    lastTime = currentTime;
  }
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;

  return deltaTime;
}

double SimpleTimer::getDelta() {
  return deltaTime;
}