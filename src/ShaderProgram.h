#pragma once
#include <vector>
#include "Shader.h"
class ShaderProgram {
 private:
  bool initialized;
  unsigned int id;
  std::vector<Shader> shadersToAttach;

 public:
  void init();
  void attachShader(const Shader &shader);
  void useProgram();
  bool linkedSuccessfully() const;
  unsigned int getId() const;
  std::string getLinkErrors() const;
};
