#include <engine/Input.h>

void Input::update() {
  glm::vec3 translation = glm::vec3(0.0f);
  if (window.isKeyPressed(GLFW_KEY_W)) {
    translation += glm::vec3(-1.0f, 0.0f, 0.0f);
  }
  camera.setPosition(camera.getPosition() + translation);
}