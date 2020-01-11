#pragma once

#include "Event.h"

class WindowResizeEvent : public Event {
 private:
  unsigned int width, height;

 public:
  WindowResizeEvent(const unsigned int& width, const unsigned int& height)
      : width(width), height(height) {}

  inline unsigned int getWidth() { return width; }
  inline unsigned int getHeight() { return height; }

  std::string toString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << width << ", " << height;
    return ss.str();
  }
};

class WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() = default;

  EVENT_CLASS_TYPE(WindowClose);
  EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppTickEvent : public Event {
 public:
  AppTickEvent() = default;

  EVENT_CLASS_TYPE(AppTick)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
 public:
  AppUpdateEvent() = default;

  EVENT_CLASS_TYPE(AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event {
 public:
  AppUpdateEvent() = default;

  EVENT_CLASS_TYPE(AppRender)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};