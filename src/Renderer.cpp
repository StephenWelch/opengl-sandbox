//
// Created by Stephen Welch on 11/20/2019.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "util.h"
#include "Renderer.h"
#include "Log.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const GLchar* vertexShaderSource;
const GLchar* fragmentShaderSource;

unsigned int vao;
unsigned int vbo;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


void Renderer::init() {

  Log::getLogger()->info("Initializing Renderer");

  Log::getLogger()->debug("Creating VAOs and VBOs");
  // Create a vertex array and vertex buffer with a unique id of 1
  glGenVertexArrays(1, &vao);

  glGenBuffers(1, &vbo);
  Log::getLogger()->debug("Created VAOs and VBOs");
  // Bind vao to vertex array object
  glBindVertexArray(vao);

  // Bind buffer to GL_ARRAY_BUFFER target
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // Load data into target
  // Static draw denotes that the buffer data will rarely change
  // Dynamic draw would denote that the buffer data changes frequently
  // Stream draw would denote that the buffer data changes every draw
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Sets data at location 0 in the VBO to 3 elements, each of which will be an unnormalized float
  // Stride defines the total size of the attribute, in this case 3*32 bits
  // Offset of 0
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // Enable location 0 in the VBO
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Log::getLogger()->debug("Loading shaders");
  std::string vertexShaderSourceString = util::getFileAsString("src/shaders/direct_transform.vertexshader");
  std::string fragmentShaderSourceString = util::getFileAsString("src/shaders/single_color.fragmentshader");
  vertexShaderSource = vertexShaderSourceString.c_str();
  fragmentShaderSource = fragmentShaderSourceString.c_str();

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  if(!validateShaderCompilation(vertexShader)) {
    Log::getLogger()->error("Vertex shader compilation failed:\n{}", getShaderCompilationErrors(vertexShader));
  }

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  if(!validateShaderCompilation(fragmentShader)) {
    Log::getLogger()->error("Fragment shader compilation failed:\n{}", getShaderCompilationErrors(fragmentShader));
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  if(!validateProgramCompilation(shaderProgram)) {
    Log::getLogger()->error("Shader program compilation failed:\n{}", getProgramCompilationErrors(shaderProgram));
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  Log::getLogger()->info("Finished Renderer initialization");

}


void Renderer::render() {
  // Make this shader program the active one
  glUseProgram(shaderProgram);
  // Bind the vertex array
  glBindVertexArray(vao);
  // Draw 3 vertices of the vertex array at index 0
  glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Renderer::close() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

bool Renderer::validateShaderCompilation(const unsigned int &shaderId) {
  int success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  return success == GL_TRUE;
}

bool Renderer::validateProgramCompilation(const unsigned int &programId) {
  int success;
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  Log::getLogger()->debug(success);
  return success == GL_TRUE;
}

std::string Renderer::getShaderCompilationErrors(const unsigned int &shaderId) {
  char infoLog[512];
  glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
  return std::string(infoLog);
}

std::string Renderer::getProgramCompilationErrors(const unsigned int &programId) {
  char infoLog[512];
  glGetProgramInfoLog(programId, 512, nullptr, infoLog);
  return std::string(infoLog);
}
