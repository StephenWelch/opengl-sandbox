#include <engine/Input.h>

void Input::update() {
  glm::vec3 translation = glm::vec3(0.0f);
  float dt = glfwGetTime() - lastTime;
  float speed = 2.5;
  float displacement = speed * dt;
  if (window->isKeyPressed(GLFW_KEY_W)) {
    translation += glm::vec3(0.0f, 0.0f, -displacement);
  }
  if (window->isKeyPressed(GLFW_KEY_S)) {
    translation += glm::vec3(0.0f, 0.0f, displacement);
  }
  if (window->isKeyPressed(GLFW_KEY_A)) {
    translation += glm::vec3(-displacement, 0.0f, 0.0f);
  }
  if (window->isKeyPressed(GLFW_KEY_D)) {
    translation += glm::vec3(displacement, 0.0f, 0.0f);
  }
  camera->setPosition(camera->getPosition() + translation);

  lastTime = glfwGetTime();
}