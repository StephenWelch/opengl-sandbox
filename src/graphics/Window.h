#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <util\SimpleTimer.h>

#include <string>

#define FRAME_STAT_UPDATE_INTERVAL 1.0 / 20.0

class Window {
 private:
	GLFWwindow *window;
	std::string title;
	int width;
	int height;
	SimpleTimer frameTimer;
	SimpleTimer frameStatUpdateTimer;

 public:
	Window(const char *title, int width, int height)
			: title(const_cast<char *>(title)), width(width), height(height) {};
	bool init();
	void update();
	void cleanup();
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
	double getMouseX();
	double getMouseY();
	void setTitle(std::string title);
	void clear(float r, float g, float b, float a);
	void requestClose();
	bool closeRequested();
	int getWidth() const;
	int getHeight() const;
	void setSize(int newWidth, int newHeight);
	void setVsync(const bool &on);
	void setWireframe(const bool &on);
	void setCulling(const bool &on);
	// void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	static void APIENTRY glDebugOutput(unsigned int source,
																		 unsigned int type,
																		 unsigned int id,
																		 unsigned int severity,
																		 int length,
																		 const char *message,
																		 const void *userParam);
};
