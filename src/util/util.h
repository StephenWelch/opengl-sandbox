#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Log.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <graphics/Mesh.h>

#define WINDOWS
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define FILE_PATH_PREFIX ""

#define BIT_AT(x) (1 << x)

namespace util {

  template<class T>
  struct aggregate_adapter : public T {
    template<class... Args>
    aggregate_adapter(Args&&... args) : T{ std::forward<Args> args... } {};
  };

  Mesh generateCube(const float& sideLength, const GLenum& usage);
  std::string getWorkingDirectory();
  std::string getFileAsString(const std::string& path);
  GLenum glCheckError_(const char* file, int line);
  #define glCheckError() glCheckError_(__FILE__, __LINE__)
}  // namespace util