#include "Camera.h"

#include <util\Log.h>

#include <glm\gtc\matrix_transform.hpp>

Camera::Camera(const float& fieldOfViewDegrees, const float& screenWidth,
               const float& screenHeight) {
  this->fieldOfView = glm::radians(fieldOfViewDegrees);
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  this->minViewDist = DEFAULT_MIN_VIEW_DIST;
  this->maxViewDist = DEFAULT_MAX_VIEW_DIST;
}

glm::vec3 Camera::getPosition() const { return position; }

void Camera::setPosition(const glm::vec3& position) {
  this->position = position;
}

glm::vec3 Camera::getTarget() const { return target; }

void Camera::setTarget(const glm::vec3& target) { this->target = target; }

float Camera::getFieldOfView() const { return fieldOfView; }

void Camera::setFieldOfView(const float& fieldOfView) {
  this->fieldOfView = fieldOfView;
}

float Camera::getMinViewDistance() const { return minViewDist; }

void Camera::setMinViewDistance(const float& minViewDist) {
  this->minViewDist = minViewDist;
}

float Camera::getMaxViewDistance() const { return maxViewDist; }

void Camera::setMaxViewDistance(const float& maxViewDist) {
  this->maxViewDist = maxViewDist;
}

float Camera::getScreenWidth() const { return screenWidth; }

void Camera::setScreenWidth(const float& screenWidth) {
  this->screenWidth = screenWidth;
}

float Camera::getScreenHeight() const { return screenHeight; }

void Camera::setScreenHeight(const float& screenHeight) {
  this->screenHeight = screenHeight;
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + target, WORLD_UP);
}

glm::mat4 Camera::getProjectionMatrix() const {
  return glm::perspective(fieldOfView, screenWidth / screenHeight, minViewDist,
                          maxViewDist);
}

glm::vec3 Camera::getViewXAxis() const {
  return glm::normalize(glm::cross(getTarget(), WORLD_UP));
}

glm::vec3 Camera::getViewYAxis() const {
  return glm::normalize(glm::cross(getTarget(), getViewXAxis()));
}