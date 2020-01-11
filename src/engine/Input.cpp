#include <engine/Input.h>

void Input::init() {}

void Input::update() {
  float currentTime = glfwGetTime();
  dt = currentTime - lastTime;
  mousePos = {window->getMouseX(), window->getMouseY()};

  if (!clickedIn) {
    lastMousePos = mousePos;
    clickedIn = true;
  }

  mouseDelta = mousePos - lastMousePos;

  updateCameraControls();
  updateWindowControls();

  lastTime = currentTime;
  lastMousePos = mousePos;
}

void Input::updateCameraControls() {
  glm::vec3 translation = glm::vec3(0.0f);
  glm::vec3 cameraXAxis = camera->getViewXAxis();
  glm::vec3 cameraYAxis = camera->getViewYAxis();
  float speed = 2.5;
  float displacement = speed * dt;

  if (window->isKeyPressed(GLFW_KEY_W)) {
    translation += displacement * camera->getTarget();
  }
  if (window->isKeyPressed(GLFW_KEY_S)) {
    translation -= displacement * camera->getTarget();
  }
  if (window->isKeyPressed(GLFW_KEY_A)) {
    translation -= displacement * cameraXAxis;
  }
  if (window->isKeyPressed(GLFW_KEY_D)) {
    translation += displacement * cameraXAxis;
  }
  if (window->isKeyPressed(GLFW_KEY_E)) {
    translation += displacement * cameraYAxis;
  }
  if (window->isKeyPressed(GLFW_KEY_Q)) {
    translation -= displacement * cameraYAxis;
  }
  if (window->isKeyPressed(GLFW_KEY_SPACE)) {
    translation += displacement * camera->WORLD_UP;
  }
  if (window->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
    translation -= displacement * camera->WORLD_UP;
  }

  glm::vec3 rotation = glm::vec3(0.0f);
  float sensitivity = 0.05f;
  yaw += mouseDelta.x * sensitivity;
  pitch += -mouseDelta.y * sensitivity;
  pitch = fmin(89.0f, pitch);
  pitch = fmax(-89.0f, pitch);

  glm::vec3 cameraTarget;
  cameraTarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraTarget.y = sin(glm::radians(pitch));
  cameraTarget.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  camera->setTarget(glm::normalize(cameraTarget));
  camera->setPosition(camera->getPosition() + translation);
}

void Input::updateWindowControls() {
  if (window->isKeyPressed(GLFW_KEY_ESCAPE)) {
    window->requestClose();
  }
  if (window->isKeyPressed(GLFW_KEY_F)) {
    window->setWireframe(true);
  }
  if (window->isKeyReleased(GLFW_KEY_F)) {
    window->setWireframe(false);
  }
  if (window->isKeyPressed(GLFW_KEY_C)) {
    window->setCulling(true);
  }
  if (window->isKeyReleased(GLFW_KEY_C)) {
    window->setCulling(false);
  }
}
