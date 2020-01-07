#pragma once

#include "Event.h"
#include <engine/MouseCode.h>

class MouseMovedEvent : public Event {
private:
	float x, y;
public:
	MouseMovedEvent(const float& x, const float& y) : x(x), y(y) {}

	inline float getX() const { return x; }
	inline float getY() const { return y; }

	std::string toString() {
		std::stringstream ss;
		ss << "MouseMovedEvent: " << x << ", " << y;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MouseScrolledEvent : public Event {
private:
	float xOffset, yOffset;
public:
	MouseScrolledEvent(const float& xOffset, const float& yOffset) : xOffset(xOffset), yOffset(yOffset) {}

	inline float getXOffset() const { return xOffset; }
	inline float getYOffset() const { return yOffset; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
		return ss.str();
	}
};

class MouseButtonEvent : public Event {
protected:
	MouseButtonEvent(const MouseCode& button) : button(button) {}

	MouseCode button;
public:
	inline MouseCode getMouseButton() const { return button; }
	
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
	MouseButtonPressedEvent(const MouseCode& button) : MouseButtonEvent(button) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
	MouseButtonReleasedEvent(const MouseCode& button) : MouseButtonEvent(button) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased);
};