#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <util\SimpleTimer.h>

class Window {
private:
  GLFWwindow* window;
  std::string title;
  int width;
  int height;
  bool debugOutput;
  SimpleTimer frameTimer;
public:
  Window(const char* title, const int& width, const int& height, const bool& debugOutput = false) : title(const_cast<char*>(title)), width(width), height(height), debugOutput(debugOutput) {};
  bool init();
  void update();
  bool isKeyPressed(const int& key);
  bool isKeyReleased(const int& key);
  double getMouseX();
  double getMouseY();
  void setTitle(std::string title);
  void clear(const float& r, const float& g, const float& b, const float& a);
  void close();
  bool closeRequested();
  int getWidth() const;
  int getHeight() const;
  void setSize(const int& newWidth, const int& newHeight);
  void setVsync(const bool& on);
  void setWireframe(const bool& on);
  //void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  static void glDebugOutput(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam);
};
