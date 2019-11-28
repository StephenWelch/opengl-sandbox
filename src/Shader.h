#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
 private:
  std::string filePath;
  GLuint id;
  GLenum type;
 public:
  Shader(const GLenum &type, const std::string &filePath) : type(type), filePath(filePath){};
  ~Shader();
  void init();
  GLuint getId() const;
  bool compiledSuccessfully() const;
  std::string getCompilationErrors() const;
};