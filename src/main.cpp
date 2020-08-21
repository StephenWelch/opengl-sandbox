#include <engine/Application.h>

#include <memory>
#include <game/Game.h>

int main() {
	auto app = Application();
	auto game = new Game();

	app.init();
	app.pushLayer(game);

	app.start();
}