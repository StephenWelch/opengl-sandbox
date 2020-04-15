#pragma once
#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <glad/glad.h>

#include <string>

class Texture {
public:
		enum class TextureType { SPECULAR, DIFFUSE, EMISSIVE, HEIGHT, AMBIENT };

		Texture(const TextureType& type, const std::string& filePath,
						const unsigned int& textureUnit)
						:type(type),
						 filePath(filePath),
						 fileExtension(filePath.substr(filePath.find('.')+1)),
						 textureUnit(textureUnit) { };

		void init();
		void bind();
		void cleanup();
		TextureType getType() const;
		unsigned int getId() const;
		unsigned int getTextureUnit() const;
		unsigned int getTextureUnitNum() const;

private:
		TextureType type;
		std::string filePath;
		std::string fileExtension;
		unsigned int textureUnit;
		unsigned int id{};

		void createTexture(int width, int height, int nrChannels,
						const unsigned char* data);
};
