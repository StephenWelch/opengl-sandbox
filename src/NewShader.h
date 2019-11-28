#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

class NewShader {
 private:
  std::string vertexPath, fragmentPath;
  GLuint programId;

  bool shaderCompiledSuccessfully(const GLuint &shaderId) const;
  std::string getShaderCompilationErrors(const GLuint &shaderId) const;
  bool programLinkedSuccessfully(const GLuint &programId) const;
  std::string getProgramLinkErrors(const GLuint &programId) const;

 public:
  NewShader(const std::string &vertexPath, const std::string &fragmentPath)
      : vertexPath(vertexPath), fragmentPath(fragmentPath){};
  void init();
  void use();
  void cleanup();
};
