#pragma once
#include <vector>
#include "Shader.h"
class ShaderProgram {
 private:
  bool initialized;
  GLuint id;
  std::vector<Shader> shadersToAttach;
 public:
  void init();
  void cleanup();
  void attachShader(const Shader &shader);
  void useProgram();
  bool linkedSuccessfully() const;
  GLuint getId() const;
  std::string getLinkErrors() const;
};
