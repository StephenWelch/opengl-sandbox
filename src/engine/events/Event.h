#pragma once

#include <util/util.h>

#include <functional>
#include <string>

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  AppTick,
  AppUpdate,
  AppRender,
  KeyPressed,
  KeyReleased,
  KeyTyped,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

enum class EventCategory {
  None = 0,
  Application = BIT_AT(1),
  Input = BIT_AT(2),
  Keyboard = BIT_AT(3),
  Mouse = BIT_AT(4),
  MouseButton = BIT_AT(5)
};

#define EVENT_CLASS_TYPE(type)                                  \
  static EventType getStaticType() { return EventType::type; }; \
  virtual EventType() getEventType() const override {           \
    return getStaticType();                                     \
  };                                                            \
  virtual std::string getName() const override { return #type; };
#define EVENT_CLASS_CATEGORY(category) \
  virtual int getCategoryFlags() const override { return category; };

class Event {
 public:
  bool handled = false;

  virtual EventType getEventType() const = 0;
  virtual std::string getName() const = 0;
  virtual int getCategoryFlags() const = 0;
  virtual std::string toString() const { return getName(); }

  inline bool isInCategory(const EventCategory& category) {
    return category & getCategoryFlags();
  }
};

class EventDispatcher {
 private:
  Event& event;

 public:
  EventDispatcher(Event& event) : event(event);

  template <typename T, typename F>
  bool dispatch(const F& func) {
    if (event.getEventType() == T::getStaticType()) {
      event.handled = func(static_cast<T&>(event));
      return true;
    }
    return false;
  }

  inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.toString();
  }
};