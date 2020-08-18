#pragma once
#include <spdlog/spdlog.h>

#include "spdlog/sinks/stdout_color_sinks.h"

class Log {
 public:
	static void init();
	inline static std::shared_ptr<spdlog::logger> &getLogger() { return logger; }

 private:
	static std::shared_ptr<spdlog::logger> logger;
};

#define LOG_TRACE(...) Log::getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) Log::getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) Log::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Log::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::getLogger()->critical(__VA_ARGS__)