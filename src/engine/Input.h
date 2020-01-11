#pragma once
#include <memory>
#include <graphics/Window.h>
#include <graphics/Camera.h>

class Input {
private:
  const std::unique_ptr<Window>& window;
  const std::unique_ptr<Camera>& camera;

  float lastTime = 0.0f;
  float dt = 0.0f;
  glm::vec2 mousePos;
  glm::vec2 mouseDelta;
  glm::vec2 lastMousePos;
  float pitch = 0.0f;
  float yaw = -90.0f;
  bool clickedIn = false;
public:
  Input( const std::unique_ptr<Window>& window, const std::unique_ptr<Camera>& camera) : window(window), camera(camera) {};
  void init();
  void update();
  void updateCameraControls();
  void updateWindowControls();
};