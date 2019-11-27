//
// Created by Stephen Welch on 11/20/2019.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "Log.h"

bool Window::init() {

  Log::getLogger()->info("Starting Window initialization");

  // Initialize GLFW
  glfwInit();

  // Set OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Set OpenGL profile to Core
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(debugOutput) {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, nullptr);
      glDebugMessageControl(GL_DEBUG_SOURCE_API,
                            GL_DEBUG_TYPE_ERROR,
                            GL_DEBUG_SEVERITY_HIGH,
                            0, nullptr, GL_TRUE);
    }
  }

  // Create a window object
  window = glfwCreateWindow(800, 600, "Game", nullptr, nullptr);

  // If initialization fails, print an error message and terminate GLFW
  if (window == nullptr) {
    Log::getLogger()->error("Failed to create GLFW window, terminating");
    glfwTerminate();
    return false;
  }

  // Selects this window for any future OpenGL calls
  glfwMakeContextCurrent(window);

  // Initialize GLAD before calling OpenGL
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  // Set OpenGL viewport dimensions to same size as window
  glViewport(0, 0, 800, 600);

  // Set the callback for window resizing
//  glfwSetFramebufferSizeCallback(window, [this](GLFWwindow* window, int width, int height){
//    setSize(width, height);
//  });

  Log::getLogger()->info("Window initialization finished");

  return true;
}

void Window::update() {
  if(!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  } else {
    glfwTerminate();
  }
}

void Window::setSize(const int &newWidth, const int &newHeight) {
  this->width = newWidth;
  this->height = newHeight;
  glViewport(0, 0, width, height);
}

bool Window::isKeyPressed(const int &key) {
  return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::isKeyReleased(const int &key) {
  return glfwGetKey(window, key) == GLFW_RELEASE;
}

void Window::setTitle(char *&p_title) {
  this->title = p_title;
  glfwSetWindowTitle(window, p_title);
}

void Window::clear(const float &r, const float &g, const float &b, const float &a) {
  // Set a color to clear the screen to
  glClearColor(r, g, b, a);
  // Clears the color buffer with the color set by glClearColor
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::close() {
  glfwSetWindowShouldClose(window, true);
}

bool Window::closeRequested() {
  return static_cast<bool>(glfwWindowShouldClose(window));
}

void Window::glDebugOutput(unsigned int source,
                            unsigned int type,
                            unsigned int id,
                            unsigned int severity,
                            int length,
                            const char *message,
                            const void *userParam)
{
  // ignore non-significant error/warning codes
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " <<  message << std::endl;

  switch (source)
  {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
  } std::cout << std::endl;

  switch (type)
  {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
  } std::cout << std::endl;

  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
  } std::cout << std::endl;
  std::cout << std::endl;
}
