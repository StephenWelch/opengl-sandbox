#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <util\Log.h>

void Camera::update()
{
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
  return glm::lookAt(position, position + target, glm::vec3(0.0f, 1.0f, 0.0f));
}
