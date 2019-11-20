#include "Window.h"

int main() {

    auto* window = new Window("Game", 800, 600);
    window->init();

    while(!window->closeRequested()) {
      window->clear(0, 1, 0, 0);
      window->update();
    }
    window->close();
    delete window;

    return 0;
}