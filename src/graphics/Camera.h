#pragma once
#include <glm/glm.hpp>

#define DEFAULT_MIN_VIEW_DIST 0.1f
#define DEFAULT_MAX_VIEW_DIST 100.0f

class Camera {
 private:
	float fieldOfView;
	float minViewDist, maxViewDist;
	float screenWidth, screenHeight;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);

 public:
	const glm::vec3 WORLD_UP = {0.0f, 1.0f, 0.0f};

	Camera(float fieldOfView, float screenWidth,
				 float screenHeight);

	glm::vec3 getPosition() const;
	void setPosition(const glm::vec3 &position);
	glm::vec3 getTarget() const;
	void setTarget(const glm::vec3 &target);
	float getFieldOfView() const;
	void setFieldOfView(float fieldOfView);
	float getMinViewDistance() const;
	void setMinViewDistance(float minViewDist);
	float getMaxViewDistance() const;
	void setMaxViewDistance(float maxViewDist);
	float getScreenWidth() const;
	void setScreenWidth(float screenWidth);
	float getScreenHeight() const;
	void setScreenHeight(float screenHeight);
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getViewXAxis() const;
	glm::vec3 getViewYAxis() const;
};
