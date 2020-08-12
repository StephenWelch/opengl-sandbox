#pragma once
#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <glad/glad.h>

#include <string>

class Texture {
public:
		enum class TextureType { SPECULAR, DIFFUSE, EMISSIVE, HEIGHT, AMBIENT };

		class TextureData {
		public:
				TextureData(const std::string& filePath) : filePath(filePath) {};
				void load();
				void cleanup();
				auto getFilePath() const { return this->filePath; };
				auto getWidth() const { return this->width; };
				auto getHeight() const { return this->height; };
				auto getColorChannels() const { return this->colorChannels; };
				unsigned char* getData() const { return this->data; };
		private:
				std::string filePath;
				int width{}, height{};
				GLenum colorChannels{};
				unsigned char* data{};
		};

		Texture(const TextureType& type,
						const unsigned int& textureUnit)
						:type(type),
						 textureUnit(textureUnit) { };

		virtual void init() = 0;
		virtual void bind();
		virtual void cleanup() = 0;

		auto getType() const { return this->type; };
		auto getId() const { return this->id; };
		auto getTextureUnit() const { return this->textureUnit; };

protected:
		// OpenGL information
		TextureType type;
		unsigned int textureUnit;
		unsigned int id{};
};

class Texture2d : public Texture {
public:
		Texture2d(const TextureType& type, const unsigned int& textureUnit, const std::string& filePath) :
		Texture(type, textureUnit),
		filePath(filePath) {};

		void init() override;
		void cleanup() override;

private:
		// File information
		std::string filePath;
};

class TextureCubeMap : public Texture {
public:
		TextureCubeMap(const TextureType& type, const unsigned int& textureUnit, const std::array<std::string, 6>& filePaths) :
		Texture(type, textureUnit),
		filePaths(filePaths) {};

		void init() override;
		void cleanup() override;

private:
		std::array<std::string, 6> filePaths;
};
