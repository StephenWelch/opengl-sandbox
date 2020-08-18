#pragma once

#include <engine/input/KeyCode.h>

#include <sstream>

#include "Event.h"

class KeyEvent : public Event {
 protected:
	KeyEvent(KeyCode keyCode)
			: keyCode(keyCode) {};

	KeyCode keyCode;

 public:
	KeyCode getKeyCode() const { return keyCode; };

	EVENT_CLASS_CATEGORY(EventCategory::Keyboard | EventCategory::Input);
};

class KeyPressedEvent : public KeyEvent {
 private:
	int repeatCount;

 public:
	KeyPressedEvent(KeyCode keyCode, int repeatCount)
			: KeyEvent(keyCode), repeatCount(repeatCount) {};

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
	KeyReleasedEvent(KeyCode keyCode)
			: KeyEvent(keyCode) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased);
};

class KeyTyped : public KeyEvent {
 public:
	KeyTyped(KeyCode keyCode)
			: KeyEvent(keyCode) {};

	std::string toString() const override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyTyped);
};