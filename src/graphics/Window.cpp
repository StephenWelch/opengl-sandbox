//
// Created by Stephen Welch on 11/20/2019.
//

#include <engine/Core.h>
#include <graphics/Window.h>
#include <util/Log.h>
#include <engine/events/ApplicationEvent.h>
#include <engine/events/KeyEvent.h>
#include <engine/events/MouseEvent.h>
#include <engine/input/MouseCodes.h>

#include <iostream>

bool Window::init() {
	LOG_INFO("Starting Window initialization");

	// Initialize GLFW
	glfwInit();
	// Clear errors
	// glGetError();

	glfwDefaultWindowHints();
	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set OpenGL profile to Core
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (ENABLE_GL_DEBUG_OUTPUT) {
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	}

	// Create a window object
	window = glfwCreateWindow(width, height, "Game", NULL, NULL);
	// If initialization fails, print an error message and terminate GLFW
	if (window==NULL) {
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

	if (ENABLE_GL_DEBUG_OUTPUT) {
		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			LOG_INFO("Enabling debug output");
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
														nullptr, GL_TRUE);
		}
	}

	glfwSetErrorCallback(glfwErrorCallback);
	glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set OpenGL viewport dimensions to same size as window
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);
		userWindow.setSize(width, height);

		WindowResizeEvent event(width, height);
		userWindow.getEventCallback()(event);
	});

	glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		userWindow.getEventCallback()(event);
	});

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);

		switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent event(static_cast<KeyCode>(key), 0);
				userWindow.getEventCallback()(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(static_cast<KeyCode>(key));
				userWindow.getEventCallback()(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(static_cast<KeyCode>(key), 1);
				userWindow.getEventCallback()(event);
				break;
			}
		}
	});

	glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int keycode) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(static_cast<KeyCode>(keycode));
		userWindow.getEventCallback()(event);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);

		switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(static_cast<MouseCode>(button));
				userWindow.getEventCallback()(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
				userWindow.getEventCallback()(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		userWindow.getEventCallback()(event);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos) {
		Window &userWindow = *(Window *)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		userWindow.getEventCallback()(event);
	});

	frameStatUpdateTimer.mark();

	LOG_INFO("Window initialization finished");

	return true;
}

void Window::update() {
	glfwPollEvents();
	glfwSwapBuffers(window);
	if (ENABLE_PERF_TRACE) {
		frameTimer.mark();
		if (glfwGetTime() - frameStatUpdateTimer.getLastMarkTime() >
				FRAME_STAT_UPDATE_INTERVAL) {
			double frameTime = frameTimer.getMovingAverage();
			double fps = 1.0/frameTime;
			std::string title = "FPS: " + std::to_string(fps) +
					" MPF: " + std::to_string(frameTime*1000.0);
			setTitle(title.c_str());
			frameStatUpdateTimer.mark();
		}
	}
}

void Window::cleanup() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::setSize(int newWidth, int newHeight) {
	this->width = newWidth;
	this->height = newHeight;
	LOG_DEBUG("Set window size to {}x{}", width, height);
	glViewport(0, 0, width, height);
}

void Window::setTitle(std::string p_title) {
	this->title = p_title;
	glfwSetWindowTitle(window, p_title.c_str());
}

void Window::setEventCallback(const std::function<void(Event &)> &callback) {
	this->eventCallback = callback;
}

void Window::clear(float r, float g, float b,
									 float a) {
	// Set a color to clear the screen to
	glClearColor(r, g, b, a);
	// Clears the color buffer with the color set by glClearColor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::requestClose() {
	glfwSetWindowShouldClose(window, true);

	WindowCloseEvent event;
	getEventCallback()(event);
}

bool Window::isCloseRequested() const {
	return glfwWindowShouldClose(window)==GL_TRUE;
}

void Window::setVsync(const bool &on) {
	if (on) {
		glfwSwapInterval(1);
	} else {
		glfwSwapInterval(0);
	}
}

void Window::setWireframe(const bool &on) {
	if (on) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Window::setCulling(const bool &on) {
	if (on) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

bool Window::isKeyPressed(KeyCode key) {
	auto state = glfwGetKey(window, static_cast<int32_t>(key));
	return state==GLFW_PRESS || state==GLFW_REPEAT;
}

bool Window::isKeyReleased(KeyCode key) {
	auto state = glfwGetKey(window, static_cast<int32_t>(key));

	return state==GLFW_RELEASE;
}

bool Window::isMouseButtonPressed(MouseCode button) {
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
	return state==GLFW_PRESS;
}

std::pair<float, float> Window::getMousePosition() {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return {(float)xpos, (float)ypos};
}

float Window::getMouseX() {
	auto[x, y] = getMousePosition();
	return x;
}
float Window::getMouseY() {
	auto[x, y] = getMousePosition();
	return y;
}

void APIENTRY Window::glDebugOutput(unsigned int source, unsigned int type, unsigned int id, unsigned int severity,
																		int length, const char *message, const void *userParam) {
	// ignore non-significant error/warning codes
	if (id==131169 || id==131185 || id==131218 || id==131204) return;

	std::string logMessage, sourceMessage, typeMessage, severityMessage;

	switch (source) {
		case GL_DEBUG_SOURCE_API:sourceMessage = "Source: API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:sourceMessage = "Source: Window System";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:sourceMessage = "Source: Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:sourceMessage = "Source: Third Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:sourceMessage = "Source: Application";
			break;
		case GL_DEBUG_SOURCE_OTHER:sourceMessage = "Source: Other";
			break;
	}

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:typeMessage = "Type: Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:typeMessage = "Type: Deprecated Behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:typeMessage = "Type: Undefined Behaviour";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:typeMessage = "Type: Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:typeMessage = "Type: Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:typeMessage = "Type: Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:typeMessage = "Type: Push Group";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:typeMessage = "Type: Pop Group";
			break;
		case GL_DEBUG_TYPE_OTHER:typeMessage = "Type: Other";
			break;
	}

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:severityMessage = "Severity: high";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:severityMessage = "Severity: medium";
			break;
		case GL_DEBUG_SEVERITY_LOW:severityMessage = "Severity: low";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:severityMessage = "Severity: notification";
			break;
	}

	LOG_ERROR("\nDebug message ({}): \n{}\n{}\n{}\n{}", id, message,
						sourceMessage, typeMessage, severityMessage);
}

void Window::glfwErrorCallback(int error, const char *description) {
	LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}
