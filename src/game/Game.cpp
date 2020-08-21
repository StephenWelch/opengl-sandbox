//
// Created by Stephen Welch on 8/21/2020.
//

#include <engine/Application.h>
#include "Game.h"

Game::Game() : Layer("Game") {
	camera = std::make_unique<Camera>(45.0f, 1600, 1000);
	renderer = std::make_unique<Renderer>(camera, 1600, 1000);
	input = std::make_unique<Input>(Application::get().getWindow(), camera);
}

void Game::onAttach() {
	renderer->init();

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

	renderer->getDirectionalLights()->updateAll();
	renderer->getPointLights()->updateAll();
	renderer->getSpotLights()->updateAll();
}
void Game::onDetach() {
	renderer->cleanup();
}
void Game::onUpdate(double ts) {
	input->update();

	flashlight->position = glm::vec4(camera->getPosition(), 0.0f);
	flashlight->direction = glm::vec4(camera->getTarget(), 0.0f);
	renderer->getSpotLights()->update(flashlight);

	renderer->render();
}
void Game::onEvent(Event &event) {
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(input->onKeyPressOrRelease));
	dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(input->onKeyPressOrRelease));
	dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(input->onMouseMove));
}

void Game::onImGuiRender() {

}
