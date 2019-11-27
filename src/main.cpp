#include <memory>
#include "Game.h"

int main() {

  auto game = std::make_unique<Game>();
  game->run();
  
}