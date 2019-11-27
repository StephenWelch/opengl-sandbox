#include "util.h"

namespace util {

  std::string util::getWorkingDirectory() {
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
      return "";
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    return std::string(cCurrentPath);
  }

  /**
   * Reads a file into a string.
   * https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
   * @param path The path to the file to read from
   * @return The file's contents as a a string
   */
  std::string util::getFileAsString(const std::string &path) {
    Log::getLogger()->debug("Loading resource: {}", path);
    Log::getLogger()->debug(util::getWorkingDirectory());
    std::ifstream file(FILE_PATH_PREFIX + path);
    if (!file) {
      Log::getLogger()->error("Error opening: {}", path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

  GLenum util::glCheckError_(const char* file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
      std::string error;
      switch (errorCode) {
        case GL_INVALID_ENUM:
          error = "INVALID_ENUM";
          break;
        case GL_INVALID_VALUE:
          error = "INVALID_VALUE";
          break;
        case GL_INVALID_OPERATION:
          error = "INVALID_OPERATION";
          break;
        case GL_STACK_OVERFLOW:
          error = "STACK_OVERFLOW";
          break;
        case GL_STACK_UNDERFLOW:
          error = "STACK_UNDERFLOW";
          break;
        case GL_OUT_OF_MEMORY:
          error = "OUT_OF_MEMORY";
          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
          error = "INVALID_FRAMEBUFFER_OPERATION"; break;
      }
      std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
  }

  //  const char* getFileAsCharArray(const std::string &path) {
  //    std::string contents = getFileAsString(path);
  //    char contentsArray[contents.size() + 1];
  //    contents.copy(contentsArray, contents.size() + 1);
  //    contentsArray[contents.size()] = '\0';
  //    return contentsArray;
  //  }

}