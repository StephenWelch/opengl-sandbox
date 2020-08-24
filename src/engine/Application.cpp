#include "Application.h"

#include <iostream>
#include <memory>

Application *Application::instance = nullptr;

Application::Application() {
	ENGINE_ASSERT(!instance, "Application already exists!");
	instance = this;

	window = std::make_unique<Window>("Game", 1600, 1000);
	imguiLayer = new ImGuiLayer();

	Log::init();
	Log::getLogger()->set_level(LOG_LEVEL);
}

void Application::init() {
	window->setEventCallback(BIND_EVENT_FN(onEvent));

	window->init();

	imguiLayer->blockEvents(false);
	pushOverlay(imguiLayer);

	// Perform any config after resources are initialized
	window->setCulling(true);
	window->setVsync(false);
}

int Application::start() {
	while (running) {
		window->clear(0.25f, 0.25f, 0.25f, 1.0f);

		for(auto *layer : layerStack) {
			layer->onUpdate(updateTimer.getDelta());
		}

		if(imguiVisible) {
			imguiLayer->begin();
			for(auto *layer : layerStack) {
				layer->onImGuiRender();
			}
			imguiLayer->end();
		}

		// Clear screen, write rendering data to GPU, swap framebuffers
		window->update();

		updateTimer.mark();
	}
	window->cleanup();

	return 0;
}

void Application::onEvent(Event &event) {
	EventDispatcher dispatcher(event);

	dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

	for(auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
		if(event.Handled) {
			break;
		}
		(*it)->onEvent(event);
	}
}

bool Application::onWindowClose(WindowCloseEvent &event) {
	LOG_DEBUG("Close requested");
	running = false;
	return true;
}

void Application::pushLayer(Layer *layer) {
	layerStack.pushLayer(layer);
	layer->onAttach();
}
void Application::pushOverlay(Layer *layer) {
	layerStack.pushOverlay(layer);
	layer->onAttach();
}

void Application::setImguiVisible(bool visible) {
	this->imguiVisible = visible;
}
