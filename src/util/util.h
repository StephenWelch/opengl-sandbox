#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Log.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOWS
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define FILE_PATH_PREFIX ""

namespace util {

  std::string getWorkingDirectory();
  std::string getFileAsString(const std::string& path);
  GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
}  // namespace util