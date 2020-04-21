//
// Created by Stephen Welch on 4/14/2020.
//

#include <util/Loader.h>

//Texture TextureLoader::load()
//{
//		// Load the texture
//		int width, height, nrChannels;
//		unsigned char* data =
//						stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
//
//		ENGINE_ASSERT(data, "Failed to load texture {}", filePath);
//
//		GLuint colorChannels = GL_RGBA;
//		if(nrChannels == 1) {
//				colorChannels = GL_RED;
//		} else if(nrChannels == 3) {
//				colorChannels = GL_RGB;
//		} else if(nrChannels == 4) {
//				colorChannels = GL_RGBA;
//		}
//
//		// Allocate texture
//		unsigned int id;
//		glGenTextures(1, &id);
//		glBindTexture(GL_TEXTURE_2D, id);
//
//		glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, width, height, 0, colorChannels,
//						GL_UNSIGNED_BYTE, data);
//
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		stbi_image_free(data);
//
//
//		return Texture(<#initializer#>, std::basic_string(), <#initializer#>);
//}
