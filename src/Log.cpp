//
// Created by Stephen Welch on 11/24/2019.
//

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::logger;

void Log::init() {
  // Color, timestamp, name of logger, message
  spdlog::set_pattern("%^[%T] %n: %v%$");
  logger = spdlog::stdout_color_mt("ENGINE");

  logger->set_level(spdlog::level::trace);
}