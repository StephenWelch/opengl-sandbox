//
// Created by Stephen Welch on 11/20/2019.
//

#ifndef LEARN_OPENGL_WINDOW_H
#define LEARN_OPENGL_WINDOW_H


#include <string>
#include <utility>
#include <GLFW/glfw3.h>

class Window {

 private:
    GLFWwindow *window;
    char* title;
    int width;
    int height;
 public:
    Window(char* title, const int &width, const int &height) : title(title), width(width), height(height) {};
    bool init();
    void update();
    bool isKeyPressed(const int &key);
    bool isKeyReleased(const int &key);
    void setTitle(char* &title);
    void clear(const float &r, const float &g, const float &b, const float &a);
    void close();
    bool closeRequested();
    void setSize(const int &newWidth, const int &newHeight);
    void resizeCallback(GLFWwindow *window, int newWidth, int newHeight);
};


#endif //LEARN_OPENGL_WINDOW_H
