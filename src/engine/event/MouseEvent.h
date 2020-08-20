#pragma once

#include "engine/event/Event.h"
#include "engine/input/MouseCodes.h"

class MouseMovedEvent : public Event {
 public:
	MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {};

	float getX() const { return m_MouseX; }
	float getY() const { return m_MouseY; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 private:
	float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event {
 public:
	MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {};

	float getXOffset() const { return m_XOffset; }
	float getYOffset() const { return m_YOffset; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
 public:
	inline MouseCode getMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
 protected:
	MouseButtonEvent(MouseCode button)
			: m_Button(button) {};

	MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
	MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
	MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};
