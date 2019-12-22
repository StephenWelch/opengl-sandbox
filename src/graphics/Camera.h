#pragma once
#include <glm/glm.hpp>
class Camera
{
private:
  glm::vec3 position;
  glm::vec3 target;
  glm::vec3 targetToCamera;
  glm::vec3 up;
  glm::vec3 right;

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
