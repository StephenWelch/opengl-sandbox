//
// Created by Stephen Welch on 8/21/2020.
//

#pragma once

#include <engine/layer/Layer.h>
#include <graphics/Camera.h>
#include <engine/input/Input.h>
#include <graphics/Renderer.h>

class Game : public Layer {
 private:
	std::shared_ptr<SpotLight> flashlight;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Input> input;

 public:
	Game();

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(double ts) override;
	void onEvent(Event &event) override;
	virtual void onImGuiRender() override;

};
