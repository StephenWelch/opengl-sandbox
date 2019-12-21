#include <memory>
#include "engine/Game.h"
#include <glm/glm.hpp>

int main() {
  auto game = std::make_unique<Game>();
  game->run();
}