//
// Created by Stephen Welch on 11/20/2019.
//

#include <iostream>
#include <glad/glad.h>
#include "Window.h"

bool Window::init() {
  // Initialize GLFW
  glfwInit();

  // Set OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Set OpenGL profile to Core
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window object
  window = glfwCreateWindow(800, 600, "Game", nullptr, nullptr);

  // If initialization fails, print an error message and terminate GLFW
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }

  // Selects this window for any future OpenGL calls
  glfwMakeContextCurrent(window);

  // Initialize GLAD before calling OpenGL
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set OpenGL viewport dimensions to same size as window
  glViewport(0, 0, 800, 600);

  // Set the callback for window resizing
//  glfwSetFramebufferSizeCallback(window, [this](GLFWwindow* window, int width, int height){
//    setSize(width, height);
//  });
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

void Window::setTitle(char *&title) {
  this->title = title;
  glfwSetWindowTitle(window, title);
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
