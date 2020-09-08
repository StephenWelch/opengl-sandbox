#pragma once

#include <util/Log.h>

#define ENABLE_ASSERTS true
#define ENABLE_GL_DEBUG_OUTPUT true
#define ENABLE_PERF_TRACE true
#define ENABLE_BREAK_ON_DEBUG_ERROR false
#define LOG_LEVEL spdlog::level::trace

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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