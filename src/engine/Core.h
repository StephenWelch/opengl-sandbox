#pragma once

#include <util/Log.h>

#define ENABLE_ASSERTS true
#define ENABLE_GL_DEBUG_OUTPUT true
#define LOG_LEVEL spdlog::level::trace

#ifdef ENABLE_ASSERTS
#define ENGINE_ASSERT(x, ...)                          \
  {                                                    \
    if (!(x)) {                                        \
      LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
      __debugbreak();                                  \
    }                                                  \
  }
#else
#define ENGINE_ASSERT(x, ...)                          \
  {                                                    \
    if (!(x)) {                                        \
      LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
    }
#endif