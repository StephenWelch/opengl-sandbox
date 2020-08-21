#pragma once

#include "engine/layer/Layer.h"

#include "engine/event/ApplicationEvent.h"
#include "engine/event/KeyEvent.h"
#include "engine/event/MouseEvent.h"

class ImGuiLayer : public Layer {
 public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onEvent(Event &e) override;

	void begin();
	void end();

	void blockEvents(bool block) { m_BlockEvents = block; }
 private:
	bool m_BlockEvents = true;
	float m_Time = 0.0f;
};
