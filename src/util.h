#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Log.h"
#include <stdio.h>  /* defines FILENAME_MAX */

#define WINDOWS
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace util {

  const std::string FILE_PATH_PREFIX = "";

  std::string getWorkingDirectory() {
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
  std::string getFileAsString(const std::string &path) {
    Log::getLogger()->debug("Loading resource: {}", path);
    Log::getLogger()->debug(util::getWorkingDirectory());
    std::ifstream file(FILE_PATH_PREFIX + path);
    if(!file) {
      Log::getLogger()->error("Error opening: {}", path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

//  const char* getFileAsCharArray(const std::string &path) {
//    std::string contents = getFileAsString(path);
//    char contentsArray[contents.size() + 1];
//    contents.copy(contentsArray, contents.size() + 1);
//    contentsArray[contents.size()] = '\0';
//    return contentsArray;
//  }

}
