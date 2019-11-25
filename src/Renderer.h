//
// Created by Stephen Welch on 11/20/2019.
//

#ifndef LEARN_OPENGL_SRC_RENDERER_H_
#define LEARN_OPENGL_SRC_RENDERER_H_

#include <string>

class Renderer {
 public:
  void init();
  void render();
  void close();
 private:
  bool validateShaderCompilation(const unsigned int &shaderId);
  std::string getShaderCompilationErrors(const unsigned int &shaderId);
  bool validateProgramCompilation(const unsigned int &shaderId);
  std::string getProgramCompilationErrors(const unsigned int &programId);
};

#endif //LEARN_OPENGL_SRC_RENDERER_H_
