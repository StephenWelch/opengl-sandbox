#include <engine/Application.h>

#include <memory>

int main() {
  auto game = std::make_unique<Application>();
  game->start();
}