//
// Created by Stephen Welch on 11/20/2019.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "util.h"
#include "Renderer.h"
#include "Log.h"

float vertices[] = {
    // first triangle
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f // top left
};
int indices[] {
  0, 1, 3, // first triangle
  1, 2, 3 // second triangle
};

const GLchar* vertexShaderSource;
const GLchar* fragmentShaderSource;

unsigned int vao;
unsigned int vbo;
unsigned int ebo;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


void Renderer::init() {

  Log::getLogger()->info("Initializing Renderer");

  Log::getLogger()->debug("Creating rendering data structures");
  // Generate vertex array and buffers
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  // Bind VAO
  glBindVertexArray(vao);
  {
    // Bind buffer to GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    {
      // Load data into target
      // Static draw denotes that the buffer data will rarely change
      // Dynamic draw would denote that the buffer data changes frequently
      // Stream draw would denote that the buffer data changes every draw
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      // Sets data at location 0 in the VBO to 3 elements, each of which will be an unnormalized float
      // Stride defines the total size of the attribute, in this case 3*32 bits
      // Offset of 0
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      // Enable location 0 in the VBO
      glEnableVertexAttribArray(0);
    }
    // glVertexAttribPointer registered this VBO as the VAO's bound VBO, so we can unbind now
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Do not unbind the EBO while the VAO is still active, because the EBO is stored in the VAO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
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
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
  Log::getLogger()->info("Finished Renderer initialization");

}


void Renderer::render() {
  glUseProgram(shaderProgram);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::close() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
}

bool Renderer::validateShaderCompilation(const unsigned int &shaderId) {
  int success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  return success == GL_TRUE;
}

bool Renderer::validateProgramCompilation(const unsigned int &programId) {
  int success;
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
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
