#pragma once
#include <graphics/Window.h>
#include <graphics/Camera.h>

class Input {
private:
  Window window;
  Camera camera;
public:
  Input(const Window& window, const Camera& camera) : window(window), camera(camera) {};
  void update();
};