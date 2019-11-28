#include <memory>
#include "Game.h"
#include <glm/glm.hpp>

int main() {

  auto game = std::make_unique<Game>();
  game->run();
  
}