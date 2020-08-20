#pragma once

#include <engine/event/KeyEvent.h>
#include <engine/event/MouseEvent.h>
#include <graphics/Camera.h>
#include <graphics/Window.h>

#include <memory>

class Input {
 private:
	const std::unique_ptr<Window> &window;
	const std::unique_ptr<Camera> &camera;

	float lastTime = 0.0f;
	float dt = 0.0f;
	glm::vec2 mousePos = {0.0f, 0.0f};
	glm::vec2 mouseDelta = {0.0f, 0.0f};
	glm::vec2 lastMousePos = {0.0f, 0.0f};
	glm::vec3 cameraVelocity = glm::vec3(0.0f);
	float pitch = 0.0f;
	float yaw = -90.0f;
	bool clickedIn = false;

 public:
	Input(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera)
			: window(window), camera(camera) {};
	void init();
	void update();
	bool onKeyPressOrRelease(KeyEvent &event);
	bool onMouseMove(MouseMovedEvent &event);
};