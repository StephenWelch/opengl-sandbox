#pragma once
#include <memory>
#include <graphics/Window.h>
#include <graphics/Camera.h>

class Input {
private:
  const std::unique_ptr<Window>& window;
  const std::unique_ptr<Camera>& camera;
  float lastTime = 0.0f;

public:
  Input( const std::unique_ptr<Window>& window, const std::unique_ptr<Camera>& camera) : window(window), camera(camera) {};
  void update();
};