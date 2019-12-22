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
  Log::getLogger()->info("Starting Window initialization");

  // Initialize GLFW
  glfwInit();
  // Clear errors
  // glGetError();

  // Set OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Set OpenGL profile to Core
  glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // if(debugOutput) {
  //  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  //  GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  //  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
  //  {
  //    glEnable(GL_DEBUG_OUTPUT);
  //    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  //    glDebugMessageCallback(glDebugOutput, nullptr);
  //    glDebugMessageControl(GL_DEBUG_SOURCE_API,
  //                          GL_DEBUG_TYPE_ERROR,
  //                          GL_DEBUG_SEVERITY_HIGH,
  //                          0, nullptr, GL_TRUE);
  //  }
  //}

  // Create a window object
  window = glfwCreateWindow(width, height, "Game", NULL, NULL);

  // If initialization fails, print an error message and terminate GLFW
  if (window == NULL) {
    Log::getLogger()->error("Failed to create GLFW window, terminating");
    glfwTerminate();
    return false;
  }

  // Selects this window for any future OpenGL calls
  glfwMakeContextCurrent(window);


  // Initialize GLAD before calling OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Log::getLogger()->error("Failed to initialize GLAD");
    return false;
  }

  Log::getLogger()->debug("OpenGL Info:");
  Log::getLogger()->debug("Vendor: {0}", glGetString(GL_VENDOR));
  Log::getLogger()->debug("Renderer: {0}", glGetString(GL_RENDERER));
  Log::getLogger()->debug("Version: {0}", glGetString(GL_VERSION));

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


  Log::getLogger()->info("Window initialization finished");

  return true;
}

void Window::update() {
  if (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    double frameTime = frameTimer.mark();
    double fps = 1.0 / frameTime;
    std::string title = "FPS: " + std::to_string(fps) + " MPF: " + std::to_string(frameTime * 1000.0);
    setTitle(title.c_str());
    glfwPollEvents();
  }
  else {
    glfwTerminate();
  }
}

void Window::setSize(const int& newWidth, const int& newHeight) {
  this->width = newWidth;
  this->height = newHeight;
  Log::getLogger()->debug("Set window size to {}x{}", width, height);
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

void Window::close() { glfwSetWindowShouldClose(window, true); }

bool Window::closeRequested() {
  return static_cast<bool>(glfwWindowShouldClose(window));
}

int Window::getWidth()
{
  return width;
}

int Window::getHeight()
{
  return height;
}

void Window::glDebugOutput(unsigned int source, unsigned int type,
  unsigned int id, unsigned int severity, int length,
  const char* message, const void* userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    std::cout << "Source: API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    std::cout << "Source: Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    std::cout << "Source: Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    std::cout << "Source: Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    std::cout << "Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    std::cout << "Source: Other";
    break;
  }
  std::cout << std::endl;

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    std::cout << "Type: Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    std::cout << "Type: Deprecated Behaviour";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    std::cout << "Type: Undefined Behaviour";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    std::cout << "Type: Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    std::cout << "Type: Performance";
    break;
  case GL_DEBUG_TYPE_MARKER:
    std::cout << "Type: Marker";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    std::cout << "Type: Push Group";
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    std::cout << "Type: Pop Group";
    break;
  case GL_DEBUG_TYPE_OTHER:
    std::cout << "Type: Other";
    break;
  }
  std::cout << std::endl;

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    std::cout << "Severity: high";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    std::cout << "Severity: medium";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    std::cout << "Severity: low";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    std::cout << "Severity: notification";
    break;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}