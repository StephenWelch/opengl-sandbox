#include "ShaderProgram.h"
#include "Log.h"
#include "util.h"

void ShaderProgram::init() {
  id = glCreateProgram();
  for (auto shader : shadersToAttach) {
    glAttachShader(id, shader.getId());
  }
  glLinkProgram(id);
  util::glCheckError();
  if (!linkedSuccessfully()) {
    Log::getLogger()->error(getLinkErrors());
  }
  initialized = true;
}

void ShaderProgram::attachShader(const Shader &shader) {
  // We can't attach a new shader after linking...
  if (!initialized) {
    shadersToAttach.emplace_back(shader);
  } else {
    Log::getLogger()->error(
        "Shader of id {} cannot be attached, program is already linked.",
        shader.getId());
  }
}

void ShaderProgram::useProgram() {
  if (initialized) {
    glUseProgram(id);
  } else {
    Log::getLogger()->error("Program must be initialized before use.");
  }
}

bool ShaderProgram::linkedSuccessfully() const {
  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  return success == GL_TRUE;
}

unsigned int ShaderProgram::getId() const { return id; }

std::string ShaderProgram::getLinkErrors() const {
  char infoLog[512];
  glGetProgramInfoLog(id, 512, nullptr, infoLog);
  return std::string(infoLog);
}
