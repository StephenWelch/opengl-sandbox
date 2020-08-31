#pragma once

#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <glad/glad.h>
#include <cstdio> /* defines FILENAME_MAX */

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

#define MAKE_HASHABLE(type, ...) \
    namespace std {\
        template<> struct hash<type> {\
            std::size_t operator()(const type &t) const {\
                std::size_t ret = 0;\
                util::hash_combine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }

namespace util {

// https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
inline void hash_combine(std::size_t& seed) { }

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	hash_combine(seed, rest...);
}

// https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t
template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
																													+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

std::string getWorkingDirectory();
std::string getFileAsString(const std::string &path);
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

}  // namespace util