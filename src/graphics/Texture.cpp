#include "Texture.h"

#include <stb_image.h>
#include <util/util.h>

#include "util/Log.h"

void Texture::TextureData::load() {

		int nrChannels;
		data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		colorChannels = GL_RGBA;
		if(nrChannels == 1) {
				colorChannels = GL_RED;
		} else if(nrChannels == 3) {
				colorChannels = GL_RGB;
		} else if(nrChannels == 4) {
				colorChannels = GL_RGBA;
		}

		ENGINE_ASSERT(data, "Failed to load texture {}", filePath)
}
void Texture::TextureData::cleanup()
{
		stbi_image_free(data);
}

void Texture::bind()
{
//		LOG_DEBUG("Binding {} to {}", filePath, textureUnit);
		glBindTextureUnit(textureUnit, id);
}

void Texture2d::init()
{
		LOG_DEBUG("Loading texture {}", filePath);
//		stbi_set_flip_vertically_on_load(true);

		glCreateTextures(GL_TEXTURE_2D, 1, &id);

		TextureData textureData(filePath);
		textureData.load();

		glTextureStorage2D(id, 1, GL_RGBA8, textureData.getWidth(), textureData.getHeight());
		glTextureSubImage2D(id, 0, 0,0 , textureData.getWidth(), textureData.getHeight(), textureData.getColorChannels(),
						GL_UNSIGNED_BYTE, textureData.getData());

		textureData.cleanup();

		glGenerateMipmap(GL_TEXTURE_2D);

		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		LOG_DEBUG("Loaded texture {}", textureData.getFilePath());
}

void Texture2d::cleanup() { }


void TextureCubeMap::init()
{
	LOG_DEBUG("Loading texture cubemap");

	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &id);

	for(size_t face = 0; face < 6; ++face) {
			TextureData textureData(filePaths[face]);
			textureData.load();

			glTextureStorage2D(id, 1, GL_RGBA8, textureData.getWidth(), textureData.getHeight());
			glTextureSubImage3D(
							id,
							0, 0, 0,
							face,
							textureData.getWidth(), textureData.getHeight(),
							1,
							textureData.getColorChannels(),
							GL_UNSIGNED_BYTE, textureData.getData()
							);

			textureData.cleanup();

			glGenerateMipmap(GL_TEXTURE_2D);

			glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

}

void TextureCubeMap::cleanup() { }
