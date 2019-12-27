#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
private:
  std::string vertexPath, fragmentPath;
  GLuint programId;

  bool shaderCompiledSuccessfully(const GLuint& shaderId) const;
  std::string getShaderCompilationErrors(const GLuint& shaderId) const;
  bool programLinkedSuccessfully(const GLuint& programId) const;
  std::string getProgramLinkErrors(const GLuint& programId) const;

public:
  Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath) {};
  void init();
  void use();
  void cleanup();
  // Wrapper functions for uniforms taken from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setFloat3(const std::string& name, const glm::vec3 value) const;
  void setFloat4(const std::string& name, const glm::vec4 value) const;
  void setVec2(const std::string& name, const glm::vec2& value) const;
  void setVec2(const std::string& name, float x, float y) const;
  void setVec3(const std::string& name, const glm::vec3& value) const;
  void setVec3(const std::string& name, float x, float y, float z) const;
  void setVec4(const std::string& name, const glm::vec4& value) const;
  void setVec4(const std::string& name, float x, float y, float z, float w);
  void setMat2(const std::string& name, const glm::mat2& mat) const;
  void setMat3(const std::string& name, const glm::mat3& mat) const;
  void setMat4(const std::string& name, const glm::mat4& mat) const;
  GLint getUniformLocation(std::string name) const;
};
