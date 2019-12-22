#pragma once
#include <memory>
#include <graphics/Window.h>
#include <graphics/Camera.h>

class Input {
private:
  const std::unique_ptr<Window>& window;
  const std::unique_ptr<Camera>& camera;

  float lastTime = 0.0f;
  float lastMouseX;
  float lastMouseY;
  float pitch = 0.0f;
  float yaw = -90.0f;
  bool clickedIn = false;

public:
  Input( const std::unique_ptr<Window>& window, const std::unique_ptr<Camera>& camera) : window(window), camera(camera) {};
  void init();
  void update();
};