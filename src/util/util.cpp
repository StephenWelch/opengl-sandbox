#include "util.h"

namespace util {

// Note: we don't need util:: qualification here if we wrap it in a namespace util {}
// block, because these fucntions aren't class members. MSVC ignores this, but other compilers
// don't.
Mesh generateCube(float sideLength, const GLenum& usage)
{
		float halfSideLength = sideLength/2.0f;
		// Defined in winding order
		std::vector<glm::vec3> vertices{
						// Back face
						{-halfSideLength, -halfSideLength, -halfSideLength},  // Bottom-left
						{halfSideLength, halfSideLength, -halfSideLength},    // top-right
						{halfSideLength, -halfSideLength, -halfSideLength},   // bottom-right
						{halfSideLength, halfSideLength, -halfSideLength},    // top-right
						{-halfSideLength, -halfSideLength, -halfSideLength},  // bottom-left
						{-halfSideLength, halfSideLength, -halfSideLength},   // top-left
						// Front face
						{-halfSideLength, -halfSideLength, halfSideLength},  // bottom-left
						{halfSideLength, -halfSideLength, halfSideLength},   // bottom-right
						{halfSideLength, halfSideLength, halfSideLength},    // top-right
						{halfSideLength, halfSideLength, halfSideLength},    // top-right
						{-halfSideLength, halfSideLength, halfSideLength},   // top-left
						{-halfSideLength, -halfSideLength, halfSideLength},  // bottom-left
						// Left face
						{-halfSideLength, halfSideLength, halfSideLength},    // top-right
						{-halfSideLength, halfSideLength, -halfSideLength},   // top-left
						{-halfSideLength, -halfSideLength, -halfSideLength},  // bottom-left
						{-halfSideLength, -halfSideLength, -halfSideLength},  // bottom-left
						{-halfSideLength, -halfSideLength, halfSideLength},   // bottom-right
						{-halfSideLength, halfSideLength, halfSideLength},    // top-right
						// Right face
						{halfSideLength, halfSideLength, halfSideLength},    // top-left
						{halfSideLength, -halfSideLength, -halfSideLength},  // bottom-right
						{halfSideLength, halfSideLength, -halfSideLength},   // top-right
						{halfSideLength, -halfSideLength, -halfSideLength},  // bottom-right
						{halfSideLength, halfSideLength, halfSideLength},    // top-left
						{halfSideLength, -halfSideLength, halfSideLength},   // bottom-left
						// Bottom face
						{-halfSideLength, -halfSideLength, -halfSideLength},  // top-right
						{halfSideLength, -halfSideLength, -halfSideLength},   // top-left
						{halfSideLength, -halfSideLength, halfSideLength},    // bottom-left
						{halfSideLength, -halfSideLength, halfSideLength},    // bottom-left
						{-halfSideLength, -halfSideLength, halfSideLength},   // bottom-right
						{-halfSideLength, -halfSideLength, -halfSideLength},  // top-right
						// Top face
						{-halfSideLength, halfSideLength, -halfSideLength},  // top-left
						{halfSideLength, halfSideLength, halfSideLength},    // bottom-right
						{halfSideLength, halfSideLength, -halfSideLength},   // top-right
						{halfSideLength, halfSideLength, halfSideLength},    // bottom-right
						{-halfSideLength, halfSideLength, -halfSideLength},  // top-left
						{-halfSideLength, halfSideLength, halfSideLength}    // bottom-left
		};

		std::vector<glm::vec3> normals{
						{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
						{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},

						{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},
						{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},

						{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
						{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},

						{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
						{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},

						{0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
						{0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},

						{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
						{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};

		std::vector<glm::vec2> textureCoords{
						// Back face
						{0.0f, 0.0f},  // Bottom-left
						{1.0f, 1.0f},  // top-right
						{1.0f, 0.0f},  // bottom-right
						{1.0f, 1.0f},  // top-right
						{0.0f, 0.0f},  // bottom-left
						{0.0f, 1.0f},  // top-left
						// Front face
						{0.0f, 0.0f},  // bottom-left
						{1.0f, 0.0f},  // bottom-right
						{1.0f, 1.0f},  // top-right
						{1.0f, 1.0f},  // top-right
						{0.0f, 1.0f},  // top-left
						{0.0f, 0.0f},  // bottom-left
						// Left face
						{1.0f, 0.0f},  // top-right
						{1.0f, 1.0f},  // top-left
						{0.0f, 1.0f},  // bottom-left
						{0.0f, 1.0f},  // bottom-left
						{0.0f, 0.0f},  // bottom-right
						{1.0f, 0.0f},  // top-right
						// Right face
						{1.0f, 0.0f},  // top-left
						{0.0f, 1.0f},  // bottom-right
						{1.0f, 1.0f},  // top-right
						{0.0f, 1.0f},  // bottom-right
						{1.0f, 0.0f},  // top-left
						{0.0f, 0.0f},  // bottom-left
						// Bottom face
						{0.0f, 1.0f},  // top-right
						{1.0f, 1.0f},  // top-left
						{1.0f, 0.0f},  // bottom-left
						{1.0f, 0.0f},  // bottom-left
						{0.0f, 0.0f},  // bottom-right
						{0.0f, 1.0f},  // top-right
						// Top face
						{0.0f, 1.0f},  // top-left
						{1.0f, 0.0f},  // bottom-right
						{1.0f, 1.0f},  // top-right
						{1.0f, 0.0f},  // bottom-right
						{0.0f, 1.0f},  // top-left
						{0.0f, 0.0f}   // bottom-left
		};

		std::vector<GLuint> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
																10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
																20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
																30, 31, 32, 33, 34, 35, 36};

		return Mesh(usage, vertices, normals, textureCoords, indices, {});
}
std::string getWorkingDirectory()
{
		char cCurrentPath[FILENAME_MAX];

		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
				return "";
		}

		cCurrentPath[sizeof(cCurrentPath)-1] = '\0'; /* not really required */
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
std::string getFileAsString(const std::string& path)
{
		LOG_DEBUG("Loading resource: {}/{}", util::getWorkingDirectory(), path);
		std::ifstream file(FILE_PATH_PREFIX+path);

		ENGINE_ASSERT(file, "Error opening: {}", path);

		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
}

GLenum glCheckError_(const char* file, int line)
{
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