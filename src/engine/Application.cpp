#include <engine/Application.h>
#include <engine/Core.h>
#include <engine/input/Input.h>
#include <graphics/Renderer.h>
#include <graphics/Window.h>

#include <iostream>
#include <memory>

int Application::start() {
	Log::init();
	Log::getLogger()->set_level(LOG_LEVEL);

	camera = std::make_unique<Camera>(45.0f, 1600, 1000);
	renderer = std::make_unique<Renderer>(camera, 1600, 1000);
	window = std::make_unique<Window>("Game", 1600, 1000);
	input = std::make_unique<Input>(window, camera);

	window->setEventCallback(BIND_EVENT_FN(onEvent));

	window->init();
	renderer->init();

	// Game setup
	gameSetupTemp();

	renderer->getDirectionalLights()->updateAll();
	renderer->getPointLights()->updateAll();
	renderer->getSpotLights()->updateAll();

	// Perform any config after resources are initialized
	window->setCulling(true);
	window->setVsync(false);

	while (running) {
		input->update();

		// Game logic
		flashlight->position = glm::vec4(camera->getPosition(), 0.0f);
		flashlight->direction = glm::vec4(camera->getTarget(), 0.0f);
		renderer->getSpotLights()->update(flashlight);

		// Clear screen, write rendering data to GPU, swap framebuffers
		window->clear(0.25f, 0.25f, 0.25f, 1.0f);
		renderer->render();
		window->update();
	}
	renderer->cleanup();
	window->cleanup();

	return 0;
}

void Application::onEvent(Event &event) {
	EventDispatcher dispatcher(event);

	dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
	dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(input->onKeyPressOrRelease));
	dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(input->onKeyPressOrRelease));
	dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(input->onMouseMove));
}

void Application::gameSetupTemp() {
	auto nanosuit = std::make_shared<Model>(GL_STATIC_DRAW, "res/nanosuit/nanosuit.obj");
	nanosuit->init();
	nanosuit->setPosition({0.0f, -1.75f, 0.0f});
	nanosuit->setScale(0.2f);

	auto skybox = std::make_shared<Skybox>(6, std::array<std::filesystem::path, 6>{"res/skybox/right.jpg",
																																								 "res/skybox/left.jpg",
																																								 "res/skybox/top.jpg",
																																								 "res/skybox/bottom.jpg",
																																								 "res/skybox/front.jpg",
																																								 "res/skybox/back.jpg"});
	skybox->init();

	flashlight =
			std::make_shared<SpotLight>(
					glm::vec3(),
					glm::vec3(),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					1.0f, 0.09, 0.032,
					glm::cos(glm::radians(12.5f)),
					glm::cos(glm::radians(15.0f)));

	renderer->addModel(nanosuit);
	renderer->setSkybox(skybox);
	renderer->getSpotLights()->addLight(flashlight);
	renderer->getDirectionalLights()->addLight(
			std::make_shared<DirectionalLight>(
					glm::vec3(-0.2f, -1.0f, -0.3f),
					glm::vec3(0.05f, 0.05f, 0.05f),
					glm::vec3(0.4f, 0.4f, 0.4f),
					glm::vec3(0.5f, 0.5f, 0.5f)),
			true
	);
	renderer->getPointLights()->addLight(
			std::make_shared<PointLight>(
					glm::vec3(0.7f, 0.2f, 2.0f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					glm::vec3(0.8f, 0.8f, 0.8f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					1.0f, 0.09, 0.032),
			true
	);
	renderer->getPointLights()->addLight(
			std::make_shared<PointLight>(
					glm::vec3(2.3f, -3.3f, -4.0f),
					glm::vec3(0.05f, 0.05f, 0.05f),
					glm::vec3(0.8f, 0.8f, 0.8f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					1.0f, 0.09, 0.032),
			true
	);
	renderer->getPointLights()->addLight(
			std::make_shared<PointLight>(
					glm::vec3(-4.0f, 2.0f, -12.0f),
					glm::vec3(0.05f, 0.05f, 0.05f),
					glm::vec3(0.8f, 0.8f, 0.8f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					1.0f, 0.09, 0.032),
			true
	);
	renderer->getPointLights()->addLight(
			std::make_shared<PointLight>(
					glm::vec3(0.0f, 0.0f, -3.0f),
					glm::vec3(0.05f, 0.05f, 0.05f),
					glm::vec3(0.8f, 0.8f, 0.8f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					1.0f, 0.09, 0.032),
			true
	);
}

bool Application::onWindowClose(WindowCloseEvent &event) {
	LOG_DEBUG("Close requested");
	running = false;
	return true;
}
