#include <engine/Game.h>
#include <memory>
#include <graphics/Window.h>
#include <util/Log.h>
#include <graphics/Renderer.h>
#include <engine/Input.h>  

int Game::run() {
  auto camera = std::make_unique<Camera>();
  auto renderer = std::make_unique<Renderer>(camera, 800, 600);
  auto window = std::make_unique<Window>("Game", 800, 600);
  auto input = std::make_unique<Input>(window, camera);

  Log::init();


  window->init();
  renderer->init();
  while (!window->closeRequested()) {
    camera->update();
    input->update();

    window->clear(0, 0, 0, 0);
    renderer->render();
    window->update();

  }
  renderer->close();
  window->close();

  return 0;
}