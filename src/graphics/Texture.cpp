#include "Texture.h"

#include <stb_image.h>
#include <util/util.h>

#include "util/Log.h"

void Texture::TextureData::load() {

	int nrChannels;
	data = stbi_load(filePath.generic_string().c_str(), &width, &height, &nrChannels, 0);

	colorChannels = GL_RGBA;
	if (nrChannels==1) {
		colorChannels = GL_RED;
	} else if (nrChannels==3) {
		colorChannels = GL_RGB;
	} else if (nrChannels==4) {
		colorChannels = GL_RGBA;
	}

	ENGINE_ASSERT(data, "Failed to load texture {}", filePath.generic_string())
}

Texture::TextureData::~TextureData() {
	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::bind() {
	glBindTextureUnit(textureUnit, id);
}

void Texture2d::init() {
	LOG_DEBUG("Loading texture {}", filePath);
//		stbi_set_flip_vertically_on_load(true);

	glCreateTextures(GL_TEXTURE_2D, 1, &id);

	TextureData textureData(filePath);
	textureData.load();

	glTextureStorage2D(id, 1, GL_RGBA8, textureData.getWidth(), textureData.getHeight());
	glTextureSubImage2D(id, 0, 0, 0, textureData.getWidth(), textureData.getHeight(), textureData.getColorChannels(),
											GL_UNSIGNED_BYTE, textureData.getData());

	glGenerateMipmap(GL_TEXTURE_2D);

	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	LOG_DEBUG("Loaded texture {}", textureData.getFilePath().generic_string());
}

void TextureCubemap::init() {
	LOG_DEBUG("Loading texture cubemap");

	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &id);

	// Use the first texture to allocate storage for the rest
	for (size_t face = 0; face < 6; ++face) {
		LOG_DEBUG("Loading face {} from {}", face, filePaths[face].generic_string());
		auto texture = TextureData(filePaths[face]);
		texture.load();

		// Allocate storage on first run
		if (face==0) {
			glTextureStorage2D(id, 1, GL_RGB8, texture.getWidth(), texture.getHeight());
		}

		glTextureSubImage3D(
				id,
				0,
				0, 0, face,
				texture.getWidth(), texture.getHeight(),
				1,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				texture.getData()
		);

	}
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
