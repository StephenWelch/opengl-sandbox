#include "Texture.h"

#include <stb_image.h>
#include <util/util.h>

#include "util/Log.h"

void Texture::init()
{
		LOG_DEBUG("Loading texture {}", filePath);
//		stbi_set_flip_vertically_on_load(true);

		// Allocate texture
		glCreateTextures(GL_TEXTURE_2D, 1, &id);

		// Load the texture
		int width, height, nrChannels;
		unsigned char* data =
						stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		ENGINE_ASSERT(data, "Failed to load texture {}", filePath);
		createTexture(width, height, nrChannels, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		LOG_DEBUG("Loaded texture {} with extension {} into id {} on unit {}.",
						filePath, fileExtension, id, textureUnit);
}

void Texture::bind()
{
//		LOG_DEBUG("Binding {} to {}", filePath, textureUnit);
		glBindTextureUnit(textureUnit, id);
}

void Texture::cleanup() { }

Texture::TextureType Texture::getType() const { return type; }

GLuint Texture::getId() const { return id; }

GLuint Texture::getTextureUnit() const { return textureUnit; }

GLuint Texture::getTextureUnitNum() const
{
		return textureUnit;
}

void Texture::createTexture(int width, int height, int nrChannels,
				const unsigned char* data)
{
		GLuint colorChannels = GL_RGBA;
		if(nrChannels == 1) {
				colorChannels = GL_RED;
		} else if(nrChannels == 3) {
				colorChannels = GL_RGB;
		} else if(nrChannels == 4) {
				colorChannels = GL_RGBA;
		}

		glTextureStorage2D(id, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(id, 0, 0,0 , width, height, colorChannels,
						GL_UNSIGNED_BYTE, data);
}