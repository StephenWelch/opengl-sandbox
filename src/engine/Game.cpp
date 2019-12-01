#include "Game.h"
#include <memory>
#include "../graphics/Window.h"
#include "../util/Log.h"
#include "../graphics/Renderer.h"

int Game::run() {
  auto renderer = std::make_unique<Renderer>();
  auto window = std::make_unique<Window>("Game", 800, 600);

  Log::init();

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