#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <util\Log.h>

void Camera::update()
{
  // Vector pointing from target to camera's position
  targetToCamera = glm::normalize(target - position);
  // Create vector orthogonal to direction camera is pointing and y-axis
  right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), targetToCamera));
  up = glm::cross(targetToCamera, right);
  view = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::getPosition()
{
  return position;
}

void Camera::setPosition(const glm::vec3& position)
{
   this->position = position;
}

glm::vec3 Camera::getTarget()
{
  return target;
}

void Camera::setTarget(const glm::vec3& target)
{
  this->target = target;
}

glm::mat4 Camera::getViewMatrix()
{
  Log::getLogger()->debug("{},{},{}", position.x,position.y, position.z);
  return glm::lookAt(position, target, up);
}
