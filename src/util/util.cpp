#include "util.h"

namespace util {

std::string getWorkingDirectory() {
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
		return "";
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	// We use forward slash for all our file paths in code, so make it consistent
	// between Windows and Linux
	std::string currentPath = std::string(cCurrentPath);
	std::replace(currentPath.begin(), currentPath.end(), '\\', '/');
	return currentPath;
}

/**
 * Reads a file into a string.
 * https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
 * @param path The path to the file to read from
 * @return The file's contents as a a string
 */
std::string getFileAsString(const std::string &path) {
	LOG_DEBUG("Loading resource: {}/{}", util::getWorkingDirectory(), path);
	std::ifstream file(FILE_PATH_PREFIX + path);

	ENGINE_ASSERT(file, "Error opening: {}", path);

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLenum glCheckError_(const char *file, int line) {
	GLenum errorCode;
	while ((errorCode = glGetError())!=GL_NO_ERROR) {
		std::string error;
		switch (errorCode) {
			case GL_INVALID_ENUM:error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:error = "INVALID_FRAMEBUFFER_OPERATION";
				break;
			default:error = "UNKNOWN ERROR";
				break;
		}
		LOG_ERROR("{} | {}({})", error, file, line);
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

}  // namespace util