#include "Texture.h"

#include <stb_image.h>
#include <util/util.h>

#include "util/Log.h"

void Texture::init()
{
		LOG_DEBUG("Loading texture {}", filePath);
//		stbi_set_flip_vertically_on_load(true);

		// Allocate texture
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// Load the texture
		int width, height, nrChannels;
		unsigned char* data =
						stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		ENGINE_ASSERT(data, "Failed to load texture {}", filePath);
		createTexture(width, height, nrChannels, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		LOG_DEBUG("Loaded texture {} with extension {} into id {} on unit {}.",
						filePath, fileExtension, id, textureUnit);
}

void Texture::bind()
{
//		LOG_DEBUG("Binding {} to {}", filePath, textureUnit);
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::cleanup() { }

Texture::TextureType Texture::getType() const { return type; }

GLuint Texture::getId() const { return id; }

GLuint Texture::getTextureUnit() const { return textureUnit; }

GLuint Texture::getTextureUnitNum() const
{
		return textureUnit-GL_TEXTURE0;
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


		glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, width, height, 0, colorChannels,
						GL_UNSIGNED_BYTE, data);
}