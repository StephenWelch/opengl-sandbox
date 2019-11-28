#include "Shader.h"
#include "util.h"

Shader::~Shader() { glDeleteShader(id); }

void Shader::init() {
  id = glCreateShader(type);
  Log::getLogger()->debug("Created shader of type {} with id {}", type, id);

  std::string source = util::getFileAsString(filePath);
  const char* source_cstr = source.c_str();

  // 4th parameter is number of string arrays, which we don't need
  glShaderSource(id, 1, &source_cstr, nullptr);

  glCompileShader(id);

  if (!Shader::compiledSuccessfully()) {
    Log::getLogger()->error(Shader::getCompilationErrors());
  }
}

GLuint Shader::getId() const { return id; }

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
