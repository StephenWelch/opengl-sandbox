#pragma once
#include <glm/glm.hpp>
class Camera
{
private:
  const float DEFAULT_MIN_VIEW_DIST = 0.1f;
  const float DEFAULT_MAX_VIEW_DIST = 100.0f;
  

  float fieldOfView;
  float minViewDist, maxViewDist;
  float screenWidth, screenHeight;

  glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
public:
  const glm::vec3 WORLD_UP = { 0.0f, 1.0f, 0.0f };

  Camera(const float& fieldOfView, const float& screenWidth, const float& screenHeight);
  
  glm::vec3 getPosition() const;
  void setPosition(const glm::vec3& position);
  glm::vec3 getTarget() const;
  void setTarget(const glm::vec3& target);
  float getFieldOfView() const;
  void setFieldOfView(const float& fieldOfView);
  float getMinViewDistance() const;
  void setMinViewDistance(const float& minViewDist);
  float getMaxViewDistance() const;
  void setMaxViewDistance(const float& maxViewDist);
  float getScreenWidth() const;
  void setScreenWidth(const float& screenWidth);
  float getScreenHeight() const;
  void setScreenHeight(const float& screenHeight);
  glm::mat4 getViewMatrix() const;
  glm::mat4 getProjectionMatrix() const;
  glm::vec3 getViewXAxis() const;
  glm::vec3 getViewYAxis() const;
};
