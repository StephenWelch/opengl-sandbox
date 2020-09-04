#pragma once
#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <glad/glad.h>

#include <string>
#include <utility>
#include <filesystem>
#include <engine/resource/Loadable.h>

class Texture : public Loadable {
 public:
	enum class TextureType { SPECULAR, DIFFUSE, EMISSIVE, HEIGHT, AMBIENT };

	class TextureData {
	 public:
		explicit TextureData(std::filesystem::path filePath) : filePath(std::move(filePath)) {};
		~TextureData();
		void load();
		auto getFilePath() const { return this->filePath; };
		auto getWidth() const { return this->width; };
		auto getHeight() const { return this->height; };
		auto getColorChannels() const { return this->colorChannels; };
		unsigned char *getData() const { return this->data; };
	 private:
		std::filesystem::path filePath;
		int width{}, height{};
		GLenum colorChannels{};
		unsigned char *data{};
	};

	Texture(TextureType type,
					unsigned int textureUnit)
			: type(type),
				textureUnit(textureUnit) {};
	~Texture();

	virtual void init() = 0;
	virtual void bind();

	auto getType() const { return this->type; };
	auto getId() const { return this->id; };
	auto getTextureUnit() const { return this->textureUnit; };

 protected:
	// OpenGL information
	TextureType type;
	unsigned int textureUnit;
	unsigned int id{};
};

class Texture2d : public virtual Texture {
 public:
	Texture2d(TextureType type, unsigned int textureUnit, std::filesystem::path filePath) :
			Texture(type, textureUnit),
			filePath(std::move(filePath)) {};

	void init() override;

 private:
	// File information
	std::string filePath;
};

class TextureCubemap : public virtual Texture {
 public:
	TextureCubemap(TextureType type, unsigned int textureUnit, std::array<std::filesystem::path, 6> filePaths) :
			Texture(type, textureUnit),
			filePaths(std::move(filePaths)) {};

	void init() override;

 private:
	std::array<std::filesystem::path, 6> filePaths;
};