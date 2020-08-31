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
	// Starts the main game loop when called
	void init();
	int start();
	void pushLayer(Layer *layer);
	void pushOverlay(Layer *layer);
	void setImguiVisible(bool visible);

	auto &getWindow() const { return window; }
	auto *getImguiLayer() const { return imguiLayer; }
	auto isImguiVisible() const { return imguiVisible; }

	Application(const Application &) = delete;
	Application &operator=(const Application &) = delete;
	Application(Application &&) = delete;
	Application &operator=(Application &&) = delete;

	static auto &get() {
		static Application application;
		return application;
	}

 private:
	Application();

	bool running = true;
	bool imguiVisible = false;
	SimpleTimer updateTimer;
	LayerStack layerStack;
	ImGuiLayer *imguiLayer;
	std::unique_ptr<Window> window;

	void onEvent(Event &event);
	bool onWindowClose(WindowCloseEvent &event);
};
