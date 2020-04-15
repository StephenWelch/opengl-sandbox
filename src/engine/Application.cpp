#include <engine/Application.h>
#include <engine/Core.h>
#include <engine/input/Input.h>
#include <graphics/Renderer.h>
#include <graphics/Window.h>

#include <iostream>
#include <memory>

int Application::start()
{
		Log::init();
		Log::getLogger()->set_level(LOG_LEVEL);

		auto camera = std::make_unique<Camera>(45.0f, 1600, 1000);
		auto renderer = std::make_unique<Renderer>(camera, 1600, 1000);
		auto window = std::make_unique<Window>("Game", 1600, 1000);
		auto input = std::make_unique<Input>(window, camera);

		window->init();
		renderer->init();

		// Perform any config after resources are initialized
		window->setCulling(true);
		window->setVsync(false);

		while (!window->closeRequested()) {
				input->update();

				// Clear screen, write rendering data to GPU, swap framebuffers
				window->clear(0.25f, 0.25f, 0.25f, 1.0f);
				renderer->render();
				window->update();
		}
		renderer->cleanup();
		window->cleanup();

		return 0;
}