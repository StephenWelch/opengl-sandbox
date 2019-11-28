#include "NewShader.h"
#include "util.h"

bool NewShader::shaderCompiledSuccessfully(const GLuint& shaderId) const {
  int success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  return success == GL_TRUE;
}

std::string NewShader::getShaderCompilationErrors(
    const GLuint& shaderId) const {
  char infoLog[512];
  glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
  return std::string(infoLog);
}

bool NewShader::programLinkedSuccessfully(const GLuint& programId) const {
  int success;
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  return success == GL_TRUE;
}

std::string NewShader::getProgramLinkErrors(
    const GLuint& programId) const {
  char infoLog[512];
  glGetProgramInfoLog(programId, 512, nullptr, infoLog);
  return std::string(infoLog);
}

void NewShader::init() {
  GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vertexSource = util::getFileAsString(vertexPath);
  std::string fragmentSource = util::getFileAsString(fragmentPath);
  const GLchar* vertexSource_cstr = vertexSource.c_str();
  const GLchar* fragmentSource_cstr = fragmentSource.c_str();

  glShaderSource(vertexId, 1, &vertexSource_cstr, nullptr);
  glShaderSource(fragmentId, 1, &fragmentSource_cstr, nullptr);

  glCompileShader(vertexId);
  glCompileShader(fragmentId);

  if (!shaderCompiledSuccessfully(vertexId)) {
    Log::getLogger()->error("Error compiling shader {}:\n{}", vertexPath,
                            getShaderCompilationErrors(vertexId));
  }
  if (!shaderCompiledSuccessfully(fragmentId)) {
    Log::getLogger()->error("Error compiling shader {}:\n{}", fragmentPath,
                            getShaderCompilationErrors(fragmentId));
  }

  programId = glCreateProgram();
  glAttachShader(programId, vertexId);
  glAttachShader(programId, fragmentId);
  glLinkProgram(programId);

  if (!programLinkedSuccessfully(programId)) {
    Log::getLogger()->error("Error linking shader program:\n{}",
                            getProgramLinkErrors(programId));
  }

  glDeleteShader(vertexId);
  glDeleteShader(fragmentId);
}

void NewShader::use() { glUseProgram(programId); }

void NewShader::cleanup() { glDeleteProgram(programId); }
