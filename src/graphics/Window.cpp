//
// Created by Stephen Welch on 11/20/2019.
//

#include <graphics/Window.h>
#include <iostream>
#include <util/Log.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

bool Window::init() {
  LOG_INFO("Starting Window initialization");

  // Initialize GLFW
  glfwInit();
  // Clear errors
  // glGetError();

  glfwDefaultWindowHints();
  // Set OpenGL version to 4.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Set OpenGL profile to Core
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  if(debugOutput) {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  }

  // Create a window object
  window = glfwCreateWindow(width, height, "Game", NULL, NULL);
  // If initialization fails, print an error message and terminate GLFW
  if (window == NULL) {
    LOG_ERROR("Failed to create GLFW window, terminating");
    glfwTerminate();
    return false;
  }

  // Selects this window for any future OpenGL calls
  glfwMakeContextCurrent(window);

  // Initialize GLAD before calling OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_ERROR("Failed to initialize GLAD");
    return false;
  }

  LOG_DEBUG("OpenGL Info:");
  LOG_DEBUG("Vendor: {0}", glGetString(GL_VENDOR));
  LOG_DEBUG("Renderer: {0}", glGetString(GL_RENDERER));
  LOG_DEBUG("Version: {0}", glGetString(GL_VERSION));

  if (debugOutput) {
    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
      LOG_INFO("Enabling debug output");
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, nullptr);
      glDebugMessageControl(GL_DONT_CARE,
        GL_DONT_CARE,
        GL_DONT_CARE,
        0, nullptr, GL_TRUE);
    }
  }

  glfwSetWindowUserPointer(window, this);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // Set OpenGL viewport dimensions to same size as window
  glViewport(0, 0, width, height);
  glEnable(GL_DEPTH_TEST);

  // Set the callback for window resizing
  glfwSetFramebufferSizeCallback(window,
    [](GLFWwindow* window, int width, int height) {
      Window& userWindow = *(Window*)glfwGetWindowUserPointer(window);
      userWindow.setSize(width, height);
    }
  );
  /*glfwSetCursorPosCallback(window, 
    [](GLFWwindow* window, double xPos, double yPos) {
      Window& userWindow = *(Window*)glfwGetWindowUserPointer(window);

    }
  );
  glfwSetMouseButtonCallback(window,
    [](GLFWwindow* window, int button, int action, int mods) {

    }
  );
  glfwSetKeyCallback(window, 
    [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    }
  );*/


  LOG_INFO("Window initialization finished");

  return true;
}

void Window::update() {
  glfwSwapBuffers(window);
  frameTimer.mark();
  double frameTime = frameTimer.getMovingAverage();
  double fps = 1.0 / frameTime;
  std::string title = "FPS: " + std::to_string(fps) + " MPF: " + std::to_string(frameTime * 1000.0);
  setTitle(title.c_str());
  glfwPollEvents();
}

void Window::cleanup()
{
  glfwTerminate();
}

void Window::setSize(const int& newWidth, const int& newHeight) {
  this->width = newWidth;
  this->height = newHeight;
  LOG_DEBUG("Set window size to {}x{}", width, height);
  glViewport(0, 0, width, height);
}

void Window::setVsync(const bool& on)
{
  if (on) {
    glfwSwapInterval(1);
  }
  else {
    glfwSwapInterval(0);
  }
}

void Window::setWireframe(const bool& on)
{
  if (on) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

bool Window::isKeyPressed(const int& key) {
  return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::isKeyReleased(const int& key) {
  return glfwGetKey(window, key) == GLFW_RELEASE;
}

double Window::getMouseX()
{
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  return x;
}

double Window::getMouseY()
{
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  return y;
}

void Window::setTitle(std::string p_title) {
  this->title = p_title;
  glfwSetWindowTitle(window, p_title.c_str());
}

void Window::clear(const float& r, const float& g, const float& b,
  const float& a) {
  // Set a color to clear the screen to
  glClearColor(r, g, b, a);
  // Clears the color buffer with the color set by glClearColor
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::requestClose() { glfwSetWindowShouldClose(window, true); }

bool Window::closeRequested() {
  return glfwWindowShouldClose(window) == GL_TRUE;
}

int Window::getWidth() const
{
  return width;
}

int Window::getHeight() const
{
  return height;
}

void Window::glDebugOutput(unsigned int source, unsigned int type,
  unsigned int id, unsigned int severity, int length,
  const char* message, const void* userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::string logMessage, sourceMessage, typeMessage, severityMessage;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    sourceMessage = "Source: API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    sourceMessage = "Source: Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    sourceMessage = "Source: Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    sourceMessage = "Source: Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    sourceMessage = "Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    sourceMessage = "Source: Other";
    break;
  }

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    typeMessage = "Type: Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    typeMessage = "Type: Deprecated Behaviour";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    typeMessage = "Type: Undefined Behaviour";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    typeMessage = "Type: Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    typeMessage = "Type: Performance";
    break;
  case GL_DEBUG_TYPE_MARKER:
    typeMessage = "Type: Marker";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    typeMessage = "Type: Push Group";
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    typeMessage = "Type: Pop Group";
    break;
  case GL_DEBUG_TYPE_OTHER:
    typeMessage = "Type: Other";
    break;
  }

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    severityMessage = "Severity: high";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    severityMessage = "Severity: medium";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    severityMessage = "Severity: low";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    severityMessage = "Severity: notification";
    break;
  }

  LOG_ERROR("\nDebug message ({}): \n{}\n{}\n{}\n{}", id, message, sourceMessage, typeMessage, severityMessage);


}