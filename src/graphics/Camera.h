#pragma once
#include <glm/glm.hpp>
class Camera
{
private:
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 right;
  glm::vec3 targetToCamera;

  glm::mat4 view;
public:
  void update();
  /*void translate(const glm::vec3& translation);
  void rotate(const glm::vec3& rotation);*/
  glm::vec3 getPosition();
  void setPosition(const glm::vec3& position);
  glm::vec3 getTarget();
  void setTarget(const glm::vec3& target);
  glm::mat4 getViewMatrix();
};
