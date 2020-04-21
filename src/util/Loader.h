//
// Created by Stephen Welch on 4/14/2020.
//

#ifndef LEARN_OPENGL_LOADER_H
#define LEARN_OPENGL_LOADER_H

#include <string>
#include <graphics/Texture.h>
#include <stb_image.h>

/**
 * Abstraction for all resource loading.
 * Will eventually handle async resource loading and error handling
 * @tparam T The resource being loaded.
 */
template<typename T>
class Loader {
public:
		virtual T load() = 0;
};

template<typename T>
class FileLoader : public Loader<T> {
public:
		FileLoader(const std::string& filePath) : filePath(filePath) {};
		std::string getFilePath() const { return filePath; };
protected:
		std::string filePath;
};

class TextureLoader : public FileLoader<Texture> {
public:
		Texture load();
};

#endif //LEARN_OPENGL_LOADER_H
