//
// Created by Stephen Welch on 11/24/2019.
//

#ifndef LEARN_OPENGL_SRC_LOG_H_
#define LEARN_OPENGL_SRC_LOG_H_

#include <spdlog/spdlog.h>

class Log {
 public:
  static void init();
  inline static std::shared_ptr<spdlog::logger>& getLogger() { return logger; }
 private:
  static std::shared_ptr<spdlog::logger> logger;
};

#endif //LEARN_OPENGL_SRC_LOG_H_
