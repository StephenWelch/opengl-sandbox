#pragma once

#include "graphics/Light.h"
#include "engine/event/Event.h"
#include "graphics/Renderer.h"
#include "graphics/Window.h"
#include "engine/input/Input.h"
#include "engine/event/ApplicationEvent.h"
#include "engine/layer/LayerStack.h"
#include "engine/imgui/ImGuiLayer.h"
#include "util/SimpleTimer.h"

class Application {
 public:
	Application();

	// Starts the main game loop when called
	int start();
	void pushLayer(Layer *layer);
	void pushOverlay(Layer *layer);

	auto &getWindow() const { return *window; }
	auto *getImguiLayer() const { return imguiLayer; }

	static auto &get() { return *instance; }

 private:

	static Application *instance;

	bool running = true;
	SimpleTimer updateTimer;
	LayerStack layerStack;
	ImGuiLayer *imguiLayer;

	void onEvent(Event &event);
	bool onWindowClose(WindowCloseEvent &event);

	// Temp game stuff
	std::shared_ptr<SpotLight> flashlight;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Window> window;
	std::unique_ptr<Input> input;

	void gameSetupTemp();
	void gameUpdateTemp();
};
