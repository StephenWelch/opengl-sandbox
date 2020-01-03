#include <engine/Game.h>
#include <memory>
#include <graphics/Window.h>
#include <util/Log.h>
#include <graphics/Renderer.h>
#include <engine/Input.h>  
#include <iostream>

int Game::run() {
  Log::init();
  Log::getLogger()->set_level(spdlog::level::trace);

  auto camera = std::make_unique<Camera>(45.0f, 800, 600);
  auto renderer = std::make_unique<Renderer>(camera, 800, 600);
  auto window = std::make_unique<Window>("Game", 800, 600, true);
  auto input = std::make_unique<Input>(window, camera);

  window->init();
  renderer->init();
  while (!window->closeRequested()) {
    input->update();

    window->clear(0, 0, 0, 0);
    renderer->render();
    window->update();
  }
  renderer->close();
  window->cleanup();

  return 0;
}