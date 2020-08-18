#pragma once

#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <glad/glad.h>
#include <graphics/Mesh.h>
#include <stdio.h> /* defines FILENAME_MAX */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Log.h"

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

std::shared_ptr<Mesh> generateCube(float sideLength,
																	 unsigned int usage,
																	 const std::vector<std::shared_ptr<Texture>> &textures);
std::string getWorkingDirectory();
std::string getFileAsString(const std::string &path);
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

}  // namespace util