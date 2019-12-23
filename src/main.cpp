#include <memory>
#include <engine/Game.h>

int main() {
  auto game = std::make_unique<Game>();
  game->run();
}