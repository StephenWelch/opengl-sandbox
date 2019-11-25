//
// Created by Stephen Welch on 11/20/2019.
//

#ifndef LEARN_OPENGL_SRC_UTIL_H_
#define LEARN_OPENGL_SRC_UTIL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Log.h"

namespace util {

  const std::string FILE_PATH_PREFIX = "../";

  /**
   * Reads a file into a string.
   * https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
   * @param path The path to the file to read from
   * @return The file's contents as a a string
   */
  std::string getFileAsString(const std::string &path) {
    Log::getLogger()->debug("Loading resource: {}", path);

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

#endif //LEARN_OPENGL_SRC_UTIL_H_
