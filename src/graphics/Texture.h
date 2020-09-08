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
		TextureData(int width, int height, unsigned int colorChannels, unsigned char *data) : width(width), height(height), colorChannels(colorChannels), data(data) {};
		explicit TextureData(const std::filesystem::path &path);
		TextureData() : TextureData("res/empty.png") {};
		~TextureData();
		auto getWidth() const { return this->width; };
		auto getHeight() const { return this->height; };
		auto getColorChannels() const { return this->colorChannels; };
		auto getData() const { return this->data; };
	 private:
		int width{}, height{};
		unsigned int colorChannels{};
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
	Texture2d(TextureType type, unsigned int textureUnit, std::shared_ptr<TextureData> data) :
			Texture(type, textureUnit),
			data(std::move(data)) {};
	Texture2d(TextureType type, unsigned int textureUnit) : Texture2d(type, textureUnit, std::make_shared<TextureData>()) {};

	void init() override;
	auto getData() const { return data; }
	void setData(const std::shared_ptr<TextureData>& data) { this->data = data; }
 private:
	std::shared_ptr<TextureData> data;
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