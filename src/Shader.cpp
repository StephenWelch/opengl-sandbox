#include "Shader.h"
#include "util.h"

void Shader::init() {
  id = glCreateShader(type);
  Log::getLogger()->debug("Created shader of type {} with id {}", type, id);

  std::string source = util::getFileAsString(filePath);
  const GLchar* source_cstr = source.c_str();

  // 4th parameter is number of string arrays, which we don't need
  glShaderSource(id, 1, &source_cstr, nullptr);

  glCompileShader(id);

  if (!Shader::compiledSuccessfully()) {
    Log::getLogger()->error("Error compiling shader {}:\n{}", filePath, getCompilationErrors());
  }
}

void Shader::cleanup() { glDeleteShader(id); }

GLuint Shader::getId() const { return id; }

GLenum Shader::getType() const { return type; }

bool Shader::compiledSuccessfully() const {
  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  return success == GL_TRUE;
}

std::string Shader::getCompilationErrors() const {
  char infoLog[512];
  glGetShaderInfoLog(id, 512, nullptr, infoLog);
  return std::string(infoLog);
}
