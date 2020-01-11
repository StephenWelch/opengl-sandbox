#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <util\SimpleTimer.h>

#include <string>

#define FRAME_STAT_UPDATE_INTERVAL 1.0 / 20.0

class Window {
 private:
  GLFWwindow* window;
  std::string title;
  int width;
  int height;
  SimpleTimer frameTimer;
  SimpleTimer frameStatUpdateTimer;

 public:
  Window(const char* title, const int& width, const int& height)
      : title(const_cast<char*>(title)), width(width), height(height){};
  bool init();
  void update();
  void cleanup();
  bool isKeyPressed(const int& key);
  bool isKeyReleased(const int& key);
  double getMouseX();
  double getMouseY();
  void setTitle(std::string title);
  void clear(const float& r, const float& g, const float& b, const float& a);
  void requestClose();
  bool closeRequested();
  int getWidth() const;
  int getHeight() const;
  void setSize(const int& newWidth, const int& newHeight);
  void setVsync(const bool& on);
  void setWireframe(const bool& on);
  void setCulling(const bool& on);
  // void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  static void glDebugOutput(GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar* message, const void* userParam);
};
