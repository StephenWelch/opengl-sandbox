#include <memory>
#include <engine/Application.h>

int main() {
  auto game = std::make_unique<Application>();
  game->start();
}