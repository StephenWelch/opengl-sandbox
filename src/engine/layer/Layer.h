#pragma once

#include <chrono>
#include "engine/Core.h"
#include "engine/event/Event.h"

class Layer {
 public:
	Layer(const std::string &name = "Layer");
	virtual ~Layer() = default;

	virtual void onAttach() {};
	virtual void onDetach() {};
	virtual void onUpdate(double ts) {};
	virtual void onImGuiRender() {};
	virtual void onEvent(Event &event) {};

	const std::string &getName() const { return m_DebugName; }
 protected:
	std::string m_DebugName;
};
