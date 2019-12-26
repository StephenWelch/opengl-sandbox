#include <engine/Input.h>

void Input::init()
{
}

// TODO Simplfy by rewriting with vec3
void Input::update() {
  float currentTime = glfwGetTime();
  float dt = currentTime - lastTime;
  float mouseX = window->getMouseX();
  float mouseY = window->getMouseY();

  if (!clickedIn) {
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    clickedIn = true;
  }
  float deltaMouseX = mouseX - lastMouseX;
  float deltaMouseY = mouseY - lastMouseY;

  if (window->isKeyPressed(GLFW_KEY_ESCAPE)) {
    window->close();
  }

  glm::vec3 translation = glm::vec3(0.0f);
  float speed = 2.5;
  float displacement = speed * dt;
  if (window->isKeyPressed(GLFW_KEY_W)) {
    translation += displacement * camera->getTarget();
  }
  if (window->isKeyPressed(GLFW_KEY_S)) {
    translation -= displacement * camera->getTarget();
  }
  if (window->isKeyPressed(GLFW_KEY_A)) {
    translation -= displacement * glm::normalize(glm::cross(camera->getTarget(), glm::vec3(0.0f, 1.0f, 0.0f)));
  }
  if (window->isKeyPressed(GLFW_KEY_D)) {
    translation += displacement * glm::normalize(glm::cross(camera->getTarget(), glm::vec3(0.0f, 1.0f, 0.0f)));
  }
  if (window->isKeyPressed(GLFW_KEY_F)) {
    window->setWireframe(true);
  }
  if (window->isKeyReleased(GLFW_KEY_F)) {
    window->setWireframe(false);
  }
  camera->setPosition(camera->getPosition() + translation);

  glm::vec3 rotation = glm::vec3(0.0f);
  float sensitivity = 0.05f;
  yaw += deltaMouseX * sensitivity;
  pitch += -deltaMouseY * sensitivity;
  if (pitch > 89.0f) {
    pitch = 89.0f;
  }
  if (pitch < -89.0f) {
    pitch = -89.0f;
  }
  glm::vec3 cameraTarget;
  cameraTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraTarget.y = sin(glm::radians(pitch));
  cameraTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  camera->setTarget(glm::normalize(cameraTarget));

  lastTime = currentTime;
  lastMouseX = mouseX;
  lastMouseY = mouseY;
}