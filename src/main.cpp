#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    glfwInit();

    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set OpenGL profile to Core
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game", NULL, NULL);

    // If initialization fails, print an error message and terminate GLFW
    if(window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Selects this window for any future OpenGL calls
    glfwMakeContextCurrent(window);

    // Initialize GLAD before calling OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set OpenGL viewport dimensions to same size as window
    glViewport(0, 0, 800, 600);

    // Set the callback for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Run the main loop while the window isn't being closed
    while(!glfwWindowShouldClose(window)) {
        // Render new pixels to window
        glfwSwapBuffers(window);
        // Poll input events, etc.
        glfwPollEvents();
    }

    // Terminate when loop exits
    glfwTerminate();

    return 0;
}