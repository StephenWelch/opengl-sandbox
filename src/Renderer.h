#pragma once

#include <string>

class Renderer {
 public:
  void init();
  void render();
  void close();
 private:
  bool validateShaderCompilation(const unsigned int &shaderId);
  std::string getShaderCompilationErrors(const unsigned int &shaderId);
  bool validateProgramCompilation(const unsigned int &shaderId);
  std::string getProgramCompilationErrors(const unsigned int &programId);
};