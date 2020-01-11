#pragma once

#include "Event.h"
#include <engine/KeyCode.h>

#include <sstream>

class KeyEvent : public Event {
protected:
	KeyEvent(const int& keyCode) : keyCode(keyCode) {};

	int keyCode;
public:
	inline int getKeyCode() const { return keyCode; };

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
};

class KeyPressedEvent : public KeyEvent {
private:
	int repeatCount;
public:
	KeyPressedEvent(const KeyCode& keyCode, const int& repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {};

	inline int getRepeatCount() const { return repeatCount; };

	std::string toString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed);
}; 

class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(const KeyCode& keyCode) : KeyEvent(keycode) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased);
};

class KeyTyped : public KeyEvent {
public:
	KeyTyped(const KeyCode& keyCode) : KeyEvent(keyCode) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped);
};