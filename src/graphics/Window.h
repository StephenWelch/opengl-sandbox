#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <engine/event/Event.h>
#include <util/SimpleTimer.h>

#include <string>
#include <engine/input/MouseCodes.h>
#include <engine/input/KeyCodes.h>

#define FRAME_STAT_UPDATE_INTERVAL 1.0 / 20.0

class Window {
 private:
	GLFWwindow *window;
	std::string title;
	int width;
	int height;
	std::function<void(Event &)> eventCallback;
	SimpleTimer frameTimer = SimpleTimer(100);
	SimpleTimer frameStatUpdateTimer = SimpleTimer(100);

	static void APIENTRY glDebugOutput(unsigned int source,
																		 unsigned int type,
																		 unsigned int id,
																		 unsigned int severity,
																		 int length,
																		 const char *message,
																		 const void *userParam);

	static void glfwErrorCallback(int error, const char *description);

 public:
	Window(const char *title, int width, int height)
			: title(const_cast<char *>(title)), width(width), height(height) {};

	bool init();
	void update();
	void cleanup();

	void setTitle(std::string title);
	void setSize(int newWidth, int newHeight);
	void setEventCallback(const std::function<void(Event &)> &callback);
	void clear(float r, float g, float b, float a);
	void requestClose();
	void setMouseLocked(bool locked);

	// OpenGL rendering options
	void setVsync(const bool &on);
	void setWireframe(const bool &on);
	void setCulling(const bool &on);

	// Getters
	auto getWidth() const { return width; }
	auto getHeight() const { return height; }
	auto getEventCallback() const { return eventCallback; }
	auto getNativeWindow() const { return window; }
	auto getFrameTimer() const { return frameTimer; }
	bool isCloseRequested() const;

	bool isKeyPressed(KeyCode key);
	bool isKeyReleased(KeyCode key);
	bool isMouseButtonPressed(MouseCode button);
	std::pair<float, float> getMousePosition();
	float getMouseX();
	float getMouseY();

};
