#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
  GLFWwindow* window;
  char* title;
  int width;
  int height;
  bool debugOutput;
public:
  Window(const char* title, const int& width, const int& height, const bool& debugOutput = false) : title(const_cast<char*>(title)), width(width), height(height), debugOutput(debugOutput), window(nullptr) {};
  bool init();
  void update();
  bool isKeyPressed(const int& key);
  bool isKeyReleased(const int& key);
  void setTitle(char*& title);
  void clear(const float& r, const float& g, const float& b, const float& a);
  void close();
  bool closeRequested();
  void setSize(const int& newWidth, const int& newHeight);
  //void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  static void glDebugOutput(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam);
};
