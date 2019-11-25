#include <memory>
#include "Window.h"
#include "Log.h"
#include "Renderer.h"
#include "util.h"

int main() {

  auto renderer = std::make_unique<Renderer>();
  auto window = std::make_unique<Window>("Game", 800, 600);

  Log::init();
  Log::getLogger()->debug("Current working directory: {}",
                          util::getWorkingDirectory());
  window->init();
  renderer->init();
  while (!window->closeRequested()) {
    window->clear(0, 0, 0, 0);
    renderer->render();
    window->update();
  }
  renderer->close();
  window->close();

  return 0;
}