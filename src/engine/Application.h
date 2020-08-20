#pragma once

#include <graphics/Light.h>
#include <engine/events/Event.h>
#include <graphics/Renderer.h>
#include <graphics/Window.h>
#include <engine/input/Input.h>
#include <engine/events/ApplicationEvent.h>

class Application {
 public:
	// Starts the main game loop when called
	int start();
 private:

	bool running = true;

	void onEvent(Event &event);
	bool onWindowClose(WindowCloseEvent &event);

	// Temp game stuff
	std::shared_ptr<SpotLight> flashlight;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Window> window;
	std::unique_ptr<Input> input;

	void gameSetupTemp();
};
